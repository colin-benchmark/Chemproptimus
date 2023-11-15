#include "FreeRTOS.h"
#include "conf_board.h"
#include "task.h"
#include <asf.h>
#include <asf/sam/drivers/wdt/wdt.h>
#include <stdio.h>

#include "debug/debug.h"

extern void vApplicationIdleHook(void) {
    wdt_restart(WDT);
}

void watchdog_init() {
    uint32_t wdt_mode;
    uint32_t timeout_value;

    log_info("Loading Watchdog component\n\r");

    /* Enable the watchdog peripheral clock */
    pmc_enable_periph_clk(ID_WDT);

    /* Configure WDT to trigger an interrupt (or reset). */
    wdt_mode = WDT_MR_WDRSTEN | WDT_MR_WDDBGHLT; /* Enable reset on timeout */

    /* Get timeout value. */
    timeout_value = wdt_get_timeout_value(CONF_WDT_TIMEOUT_MS * 1000, BOARD_FREQ_SLCK_XTAL);

    wdt_init(WDT, wdt_mode, timeout_value, timeout_value);

    int32_t timeout_period = (int)wdt_get_us_timeout_period(WDT, BOARD_FREQ_SLCK_XTAL);
    log_info("Enabled watchdog with %ld microseconds period\n\r", timeout_period);
}