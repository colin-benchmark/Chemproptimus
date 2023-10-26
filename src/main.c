#include "component_processor/component_processor.h"
#include "conf_board.h"
#include "console/console.h"
#include "device/device.h"
#include "packet_processor/packet_processor.h"
#include "rb/component_handlers.h"
#include "uart_csp/uart_csp.h"
#include "watchdog/watchdog.h"

extern void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);

/* Import Components */
ComponentProcessor component_processor[] = COMPONENT_PROCESSOR_INIT;

/**
 * \brief Called if stack overflow during execution
 */
extern void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    printf("stack overflow %x %s\r\n", &xTask, (portCHAR *)pcTaskName);
    /* If the parameters have been corrupted then inspect pxCurrentTCB to
	 * identify which task has overflowed its stack.
	 */
    for (;;) { }
}

/**
 * \brief This function is called by FreeRTOS each tick
 */
extern void vApplicationTickHook(void) {
}

extern void vApplicationMallocFailedHook(void) {
    /* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

    /* Force an assert. */
    configASSERT((volatile void *)NULL);
}

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

    /* Launch the BSS framework */
    component_processor_init(component_processor, sizeof(component_processor) / sizeof(component_processor[0]));

    /* Enable comms */
    uart_csp_init();

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* Will only get here if there was insufficient memory to create the idle task. */
    return 0;
}
