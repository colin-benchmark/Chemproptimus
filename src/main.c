#include "component_processor/component_processor.h"
#include "conf_board.h"
#include "console/console.h"
#include "device/device.h"
#include "nvm/nvm.h"
#include "packet_processor/packet_processor.h"
#include "rb/component_handlers.h"
#include "uart_csp/uart_csp.h"
#include "watchdog/watchdog.h"
#include <stdio.h>

/* Import Components */
ComponentProcessor component_processor[] = COMPONENT_PROCESSOR_INIT;

int main(void) {
    /* Initialize the SAM system */
    sysclk_init();
    board_init();

    /* Initialize the console uart */
    console_init();
    printf("-- Xantus - FreeRTOS --\n\r");

    /* Initialise Components */
    watchdog_init();
    device_init();
    nvm_init();

    /* Launch the BSS framework */
    component_processor_init(component_processor, sizeof(component_processor) / sizeof(component_processor[0]));

    /* Enable comms */
    uart_csp_init();

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* Will only get here if there was insufficient memory to create the idle task. */
    return 0;
}
