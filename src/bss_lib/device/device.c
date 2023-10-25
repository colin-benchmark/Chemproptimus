#include "device.h"
#include "device/device_attributes.h"
#include "device/device_instance.h"
#include "device/device_methods.h"
#include "status.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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

status_t device_recalculate_checksum() {
    return STATUS_NOT_IMPLEMENTED;
}
