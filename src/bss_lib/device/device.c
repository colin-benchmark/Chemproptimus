#include "FreeRTOS.h"
#include "task.h"

#include "device.h"
#include "device/device_attributes.h"
#include "device/device_instance.h"
#include "device/device_methods.h"
#include "status.h"

#include "samv71q21b.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void calculate_checksum_task(void *pvParameters) {
    uint32_t *program = (uint32_t *)IFLASH_ADDR;  // Starting address of program memory (adjust as needed)
    uint32_t checksum = 0;
    uint32_t i = 0;

    printf("Starting checksum calculation...");

    for (i = 0; i < IFLASH_SIZE; i++) {
        checksum ^= program[i];

        if (!(i % 0x1000)) {
            printf("%ld of %ld\n\r", i, IFLASH_SIZE);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
    }

    device_inst.checksum = checksum;
    printf(" Done\n\r");

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
    xTaskCreate(calculate_checksum_task, "Checksum Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    return STATUS_SUCCESS;
}

status_t device_init() {
    status_t status = STATUS_SUCCESS;

    return status;
}
