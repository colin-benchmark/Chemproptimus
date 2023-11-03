#include "firing.h"
#include "firing/firing_attributes.h"
#include "firing/firing_callbacks.h"
#include "firing/firing_instance.h"
#include "firing/firing_methods.h"
#include "status.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

status_t firing_fire_shots(int8_t thruster, int16_t shots) {
    return STATUS_NOT_IMPLEMENTED;
}

status_t firing_fire_cycles(uint16_t cycles) {
    return STATUS_NOT_IMPLEMENTED;
}

status_t firing_firing_pattern_write_callback(uint8_t *buf, uint16_t first_row, uint16_t last_row) {
    return STATUS_NOT_IMPLEMENTED;
}

status_t firing_firing_pattern_read_callback(uint8_t *buf, uint16_t first_row, uint16_t last_row) {
    return STATUS_NOT_IMPLEMENTED;
}

status_t firing_capacitor_charge_time_write_callback(uint16_t *buf) {
    return STATUS_NOT_IMPLEMENTED;
}

status_t firing_capacitor_charge_time_read_callback(uint16_t *buf) {
    return STATUS_NOT_IMPLEMENTED;
}