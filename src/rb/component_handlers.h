
#include "interfaces/device/device_interface.h"
#include "interfaces/telemetry/telemetry_interface.h"
#include "interfaces/eeprom/eeprom_interface.h"
#include "interfaces/power/power_interface.h"
#include "interfaces/firing/firing_interface.h"


#ifndef COMPONENT_HANDLERS_H
#define COMPONENT_HANDLERS_H

#define COMPONENT_PROCESSOR_INIT { \
    /* Device Component */ \
    { \
        .component_id = 0, \
        .read_handler = device_read_handler, \
        .write_handler = device_write_handler, \
        .method_handler = device_method_handler \
    }, \
    /* Telemetry Component */ \
    { \
        .component_id = 1, \
        .read_handler = telemetry_read_handler, \
        .write_handler = telemetry_write_handler, \
        .method_handler = telemetry_method_handler \
    }, \
    /* Eeprom Component */ \
    { \
        .component_id = 2, \
        .read_handler = eeprom_read_handler, \
        .write_handler = eeprom_write_handler, \
        .method_handler = eeprom_method_handler \
    }, \
    /* Power Component */ \
    { \
        .component_id = 3, \
        .read_handler = power_read_handler, \
        .write_handler = power_write_handler, \
        .method_handler = power_method_handler \
    }, \
    /* Firing Component */ \
    { \
        .component_id = 4, \
        .read_handler = firing_read_handler, \
        .write_handler = firing_write_handler, \
        .method_handler = firing_method_handler \
    } \
};

#endif
