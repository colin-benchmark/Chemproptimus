#include <asf.h>
#include <csp/arch/csp_system.h>
#include <csp/csp.h>
#include <csp/drivers/usart.h>

#include "config/conf_csp.h"
#include "led/led.h"
#include "uart_csp/uart_csp.h"

#define UART_BUFFER_SIZE 512
#define PACKET_RX_PERIOD_MS (5 / portTICK_PERIOD_MS)
#define TASK_RX_MONITOR_STACK_SIZE (512 / sizeof(portSTACK_TYPE))
#define TASK_RX_MONITOR_STACK_PRIORITY (1 + tskIDLE_PRIORITY)
#define TASK_CSP_SERVER_STACK_SIZE (2048 / sizeof(portSTACK_TYPE))
#define TASK_CSP_SERVER_STACK_PRIORITY (2 + tskIDLE_PRIORITY)

volatile uint8_t uart_rx_buffer[UART_BUFFER_SIZE];
volatile uint32_t uart_rx_head = 0;
volatile uint32_t uart_rx_tail = 0;

const char *kiss_device = NULL;
csp_usart_callback_t uart_csp_rx_callback = NULL;
void *uart_csp_user_data = NULL;
static int csp_sys_reboot_uart_csp(void);

/***********************************************************
 * Config Steps
 ***********************************************************/

static void uart_csp_hw_configure(void) {
    /* Enable the Comms UART peripheral clock */
    pmc_enable_periph_clk(UART_CSP_PERIPHERAL_ID);

    pio_configure_pin(UART_CSP_RX_PIN_IDX, UART_CSP_RX_PIN_FLAGS);
    pio_configure_pin(UART_CSP_TX_PIN_IDX, UART_CSP_TX_PIN_FLAGS);

    const sam_uart_opt_t uart_csp_settings = {
        sysclk_get_peripheral_hz(), /* UART uses PCK */
        COMMS_UART_BAUD,
        COMMS_UART_MODE,
    };

    /* Initialize UART */
    if (!uart_init(UART_CSP_PORT, &uart_csp_settings)) {
        /* Enable USART RX interrupt */
        uart_enable_interrupt(UART_CSP_PORT, US_IER_RXRDY);

        /* Enable Nested Vector Interrupt Controller */
        NVIC_EnableIRQ(UART_CSP_IRQ);

        /* Enable Tx */
        uart_enable_tx(UART_CSP_PORT);
    } else {
        /* Couldn't setup UART */
        /* TODO: Add assert */
    }
}

static void uart_csp_lib_configure() {
    /* Init CSP with address and default settings */
    csp_conf_t csp_conf;
    csp_conf_get_defaults(&csp_conf);
    csp_conf.address = CSP_ADDRESS;
    int error = csp_init(&csp_conf);
    if (error != CSP_ERR_NONE) {
        csp_log_error("csp_init() failed, error: %d", error);
        exit(1);
    }

    /* Start router task with 10000 bytes of stack (priority is only supported on FreeRTOS) */
    csp_route_start_task(500, 0);

    /* Add interface(s) */
    csp_iface_t *default_iface = NULL;
    csp_usart_conf_t conf = {
        .device = NULL,
        .baudrate = 115200, /* supported on all platforms */
        .databits = 8,
        .stopbits = 1,
        .paritysetting = 0,
        .checkparity = 0,
    };
    error = csp_usart_open_and_add_kiss_interface(&conf, CSP_IF_KISS_DEFAULT_NAME, &default_iface);
    if (error != CSP_ERR_NONE) {
        csp_log_error("failed to add KISS interface [%s], error: %d", kiss_device, error);
        exit(1);
    }

    csp_rtable_set(CSP_DEFAULT_ROUTE, 0, default_iface, CSP_NO_VIA_ADDRESS);

    csp_sys_set_reboot(csp_sys_reboot_uart_csp);
}

/***********************************************************
 * Buffer
 ***********************************************************/

static void uart_csp_buffer_push(uint8_t value) {
    uint32_t next_head = (uart_rx_head + 1) % UART_BUFFER_SIZE;

    if (next_head != uart_rx_tail) {
        uart_rx_buffer[uart_rx_head] = value;
        uart_rx_head = next_head;
    } else {
        /* TODO: Handle buffer overflow error */
        csp_log_error("CSP UART Rx Buffer Full");
        exit(1);
    }
}

static bool uart_csp_buffer_pop(uint8_t *value) {
    bool popped = false;

    if (uart_rx_tail != uart_rx_head) {
        *value = uart_rx_buffer[uart_rx_tail];
        uart_rx_tail = (uart_rx_tail + 1) % UART_BUFFER_SIZE;
        popped = true;
    }

    return popped;
}

static uint8_t uart_csp_buffer_len() {
    uint8_t diff = 0;

    if (uart_rx_tail > uart_rx_head) {
        diff = uart_rx_tail - uart_rx_head;
    } else {
        diff = uart_rx_head - uart_rx_tail;
    }

    return diff;
}

/***********************************************************
 * CSP Callbacks
 ***********************************************************/

int csp_usart_open(
    const csp_usart_conf_t *conf, csp_usart_callback_t rx_callback, void *user_data, csp_usart_fd_t *return_fd
) {
    /* Hardware should get configured based on data passed in via conf however
     * for brevity the UART HW configuration is hardcoded via uart_csp_hw_configure
     * TODO: Update uart_csp_hw_configure to use the settings in conf
     */
    uart_csp_hw_configure();
    uart_csp_rx_callback = rx_callback;
    uart_csp_user_data = user_data;
    return CSP_ERR_NONE;
}

int csp_usart_write(csp_usart_fd_t fd, const void *data, size_t data_length) {
    size_t i;
    int return_val = 0;
    const uint8_t *byte_data = (const uint8_t *)data;

    for (i = 0; i < data_length; i++) {
        int tx_byte = byte_data[i];
        while (!uart_is_tx_ready(UART_CSP_PORT)) {
            /* NOP: Wait till the transmitter is clear */
        }

        if (!uart_write(UART_CSP_PORT, tx_byte)) {
            /* write success */
            return_val++; /* record how many bytes get written */
        } else {
            /* write failure */
            return_val = CSP_ERR_TX;
            break;
        }
    }

    return return_val;
}

static int csp_sys_reboot_uart_csp(void) {
    csp_log_info("SERVICE: Reboot requested");
}

/***********************************************************
 * Tasks
 ***********************************************************/

static void uart_csp_task_rx(void *pvParameters) {
    uint8_t rx_byte = 0;
    while (1) {
        while (uart_csp_buffer_len()) {
            if (uart_csp_buffer_pop(&rx_byte)) {
                uart_csp_rx_callback(uart_csp_user_data, &rx_byte, 1, NULL);
            }
        }
        vTaskDelay(PACKET_RX_PERIOD_MS);
    }
}

static void uart_csp_task_server(void *pvParameters) {
    csp_log_info("Server task started");

    /* Create socket with no specific socket options, e.g. accepts CRC32, HMAC, XTEA, etc. if enabled during compilation */
    csp_socket_t *sock = csp_socket(CSP_SO_NONE);

    /* Bind socket to all ports, e.g. all incoming connections will be handled here */
    csp_bind(sock, CSP_ANY);

    /* Create a backlog of 10 connections, i.e. up to 10 new connections can be queued */
    csp_listen(sock, 10);

    /* Wait for connections and then process packets on the connection */
    while (1) {
        /* Wait for a new connection, 10000 mS timeout */
        csp_conn_t *conn;
        if ((conn = csp_accept(sock, 10000)) == NULL) {
            /* timeout */
            continue;
        }

        /* Read packets on connection, timout is 100 mS */
        csp_packet_t *packet;
        while ((packet = csp_read(conn, CSP_RX_TIMEOUT)) != NULL) {
            int port = csp_conn_dport(conn);
            csp_log_info("Request made to port: %d", port);

            switch (port) {
                case CSP_PRIMARY_PORT:
                    /* Process packet here */
                    if (packet != NULL) {
                        csp_log_info("Packet received on MY_SERVER_PORT: ");
                        for (size_t i = 0; i < packet->length; i++) {
                            printf("%02x ", packet->data[i]);
                        }
                        printf("\n");
                        if (!csp_send(conn, packet, 0)) {
                            csp_buffer_free(packet);
                        }
                    }
                    break;

                default:
                    /* Call the default CSP service handler, handle pings, buffer use, etc. */
                    csp_service_handler(conn, packet);
                    break;
            }
        }

        /* Close current connection */
        csp_close(conn);
    }
}

void uart_csp_init(void) {
    csp_debug_set_level(CSP_INFO, true);

    csp_log_info("Loading UART-CSP component");
    uart_csp_hw_configure();

    csp_log_info("Initializing CSP library");
    uart_csp_lib_configure();

    csp_log_info("Launching RX Monitor task");
    if (xTaskCreate(
            uart_csp_task_rx, "RX Monitor", TASK_RX_MONITOR_STACK_SIZE, NULL, TASK_RX_MONITOR_STACK_PRIORITY, NULL
        )
        != pdPASS) {
        printf("Failed to create RX Monitor task\r\n");
    }

    csp_log_info("Launching CSP Server task");
    if (xTaskCreate(
            uart_csp_task_server, "CSP Server", TASK_CSP_SERVER_STACK_SIZE, NULL, TASK_CSP_SERVER_STACK_PRIORITY, NULL
        )
        != pdPASS) {
        printf("Failed to create CSP Server task\r\n");
    }
}

/***********************************************************
 * Interrupts
 ***********************************************************/

void uart_csp_irq_handler(void) {
    uint32_t status = uart_get_status(UART_CSP_PORT);

    if (status & US_CSR_RXRDY) {
        uint8_t received_byte;
        uint32_t rx_status = uart_read(UART_CSP_PORT, &received_byte);
        if (!rx_status) {
            uart_csp_buffer_push(received_byte);
        } else {
            /* I/O Failure, UART is not ready */
        }
    }
}