#include "conf_board.h"
#include <asf.h>
#include <asf/sam/drivers/wdt/wdt.h>
#include <csp/csp.h>
#include <stdio.h>

#define TASK_WATCHDOG_STACK_SIZE (512 / sizeof(portSTACK_TYPE))
#define TASK_WATCHDOG_PRIORITY (1 + tskIDLE_PRIORITY)

static void watchdog_task(void *pvParameters) {
    while (1) {
        wdt_restart(WDT);
        vTaskDelay(CONF_WDT_KICK / portTICK_PERIOD_MS);
    }
}

void watchdog_init() {
    uint32_t wdt_mode;
    uint32_t timeout_value;

    /* Enable the watchdog peripheral clock */
    pmc_enable_periph_clk(ID_WDT);

    /* Configure WDT to trigger an interrupt (or reset). */
    wdt_mode = WDT_MR_WDRSTEN | WDT_MR_WDDBGHLT; /* Enable reset on timeout */

    /* Get timeout value. */
    timeout_value = wdt_get_timeout_value(CONF_WDT_TIMEOUT_MS * 1000, BOARD_FREQ_SLCK_XTAL);

    wdt_init(WDT, wdt_mode, timeout_value, timeout_value);

    int32_t timeout_period = (int)wdt_get_us_timeout_period(WDT, BOARD_FREQ_SLCK_XTAL);
    printf("<<< Enable watchdog with %ld microseconds period >>>\n\n\r", timeout_period);

    if (xTaskCreate(watchdog_task, "WatchdogTask", TASK_WATCHDOG_STACK_SIZE, NULL, TASK_WATCHDOG_PRIORITY, NULL)
        != pdPASS) {
        printf("Failed to create WDT task\r\n");
    }
}