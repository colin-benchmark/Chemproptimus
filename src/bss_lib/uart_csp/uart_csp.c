#include "uart_csp/uart_csp.h"
#include "config/conf_csp.h"
#include "led/led.h"
#include <asf.h>
#include <csp/csp.h>

#define UART_BUFFER_SIZE 64

volatile uint8_t uart_rx_buffer[UART_BUFFER_SIZE];
volatile uint32_t uart_rx_head = 0;
volatile uint32_t uart_rx_tail = 0;

static void uart_csp_configure(void) {
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

void uart_csp_irq_handler(void) {
    uint32_t status = uart_get_status(UART_CSP_PORT);

    if (status & US_CSR_RXRDY) {
        uint8_t received_byte;
        uint32_t rx_status = uart_read(UART_CSP_PORT, &received_byte);
        if (!rx_status) {
            uint32_t next_head = (uart_rx_head + 1) % UART_BUFFER_SIZE;

            if (next_head != uart_rx_tail) {
                uart_rx_buffer[uart_rx_head] = received_byte;
                uart_rx_head = next_head;
            } else {
                /* TODO: Handle buffer overflow error */
            }
        } else {
            /* I/O Failure, UART is not ready */
        }
    }
}

void uart_csp_init(void) {
    uart_csp_configure();

    while (1) {
        if (uart_rx_tail != uart_rx_head) {
            uint8_t received_byte = uart_rx_buffer[uart_rx_tail];
            uart_write(UART_CSP_PORT, received_byte);
            uart_rx_tail = (uart_rx_tail + 1) % UART_BUFFER_SIZE;
        } else {
            // delay_ms(500);
        }
        led0_toggle();
    }
}
