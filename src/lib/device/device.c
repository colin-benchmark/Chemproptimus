#include "FreeRTOS.h"
#include "task.h"

#include "config/conf_tasks.h"
#include "device.h"
#include "device/device_attributes.h"
#include "device/device_instance.h"
#include "device/device_methods.h"
#include "nvm/nvm.h"
#include "status.h"

#include "samv71q21b.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define TASK_DEVICE_CHECKSUM_CALCULATION_STACK configMINIMAL_STACK_SIZE

void calculate_checksum_task(void *pvParameters) {
    uint32_t *program = (uint32_t *)IFLASH_ADDR;
    size_t words_to_read = IFLASH_SIZE / sizeof(uint32_t);
    uint32_t checksum = 0;
    uint32_t i = 0;

    for (i = 0; i < words_to_read; i++) {
        checksum ^= program[i];

        if (!(i % 0x2000)) {
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }
    }

    device_inst.checksum = checksum;

    vTaskDelete(NULL);
}

status_t device_print_verison() {
    printf("Xantus Version: %d.%d.%d\n\r", device_inst.version[0], device_inst.version[1], device_inst.version[2]);
    return STATUS_SUCCESS;
}

status_t device_reboot() {
    printf("<<< Reboot requested >>>\n\r");

    while (1) {
        /* nop */
    }

    return STATUS_ERROR; /* We should never reach this line */
}

status_t device_calculate_checksum() {
    status_t status = STATUS_SUCCESS;

    printf("Calculating Device checksum\r\n");

    if (xTaskCreate(
            calculate_checksum_task,
            "Checksum Task",
            TASK_DEVICE_CHECKSUM_CALCULATION_STACK,
            NULL,
            TASK_DEVICE_CHECKSUM_CALCULATION_PRIORITY,
            NULL
        )
        != pdPASS) {
        status = STATUS_ERROR;
        printf("Failed to create Checksum task\r\n");
    }

    return status;
}

status_t device_init() {
    status_t status = STATUS_SUCCESS;

    printf("Loading Device component\n\r");

    status = device_calculate_checksum();

    return status;
}
