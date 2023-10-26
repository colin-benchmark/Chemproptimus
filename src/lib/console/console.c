#include "console/console.h"
#include "asf.h"

/**
 *  Configure UART console.
 */
void console_init(void) {
    const usart_serial_options_t uart_serial_options = {
        .baudrate = CONF_UART_BAUDRATE,
        .charlength = CONF_UART_CHAR_LENGTH,
        .paritytype = CONF_UART_PARITY,
        .stopbits = CONF_UART_STOP_BITS,
    };

    /* Configure console UART */
    sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
    stdio_serial_init(CONF_UART, &uart_serial_options);

    /* Specify that stdout should not be buffered. */
#if defined(__GNUC__)
    setbuf(stdout, NULL);
#else
    /* Already the case in IAR's Normal DLIB default configuration: printf()
	 * emits one character at a time.
	 */
#endif
}