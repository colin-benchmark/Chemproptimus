#include "device.h"
#include "device/device_attributes.h"
#include "device/device_instance.h"
#include "device/device_methods.h"
#include "status.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

status_t device_say_hello() {
    return STATUS_SUCCESS;
}

status_t device_print_verison() {
    printf("Xantus Version: %d.%d.%d", device_inst.version[0], device_inst.version[1], device_inst.version[2]);
    return STATUS_SUCCESS;
}

status_t device_reboot() {
    return STATUS_NOT_IMPLEMENTED;
}

status_t device_recalculate_checksum() {
    return STATUS_NOT_IMPLEMENTED;
}
