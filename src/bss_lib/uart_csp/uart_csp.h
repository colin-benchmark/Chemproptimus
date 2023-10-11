#include "asf.h"

#ifndef UART_CSP_H
#define UART_CSP_H

/* Port for UART Comms */
#define UART_CSP_PORT UART3

/* CLK configuraton for UART Comms */
#define UART_CSP_PERIPHERAL_ID ID_UART3

/* PIO configuration for UART Comms */
#define UART_CSP_RX_PIN_IDX PIO_PD28_IDX /* PIO_PD28A_URXD3 */
#define UART_CSP_RX_PIN_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)

#define UART_CSP_TX_PIN_IDX PIO_PD30_IDX /* PIO_PD30A_UTXD3 */
#define UART_CSP_TX_PIN_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)

/* Configuration for comms uart */

/* Configuration for comms uart IRQ handler */
#define uart_csp_irq_handler UART3_Handler
#define UART_CSP_IRQ UART3_IRQn

/* Comms Settings */
#define COMMS_UART_BAUD (115200UL)
#define COMMS_UART_MODE UART_MR_PAR_NO

void uart_csp_init(void);

#endif