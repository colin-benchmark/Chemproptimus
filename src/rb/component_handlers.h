
#include "interfaces/device/device_interface.h"
#include "interfaces/debug/debug_interface.h"
#include "interfaces/telemetry/telemetry_interface.h"
#include "interfaces/nvm/nvm_interface.h"


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
    /* Debug Component */ \
    { \
        .component_id = 1, \
        .read_handler = debug_read_handler, \
        .write_handler = debug_write_handler, \
        .method_handler = debug_method_handler \
    }, \
    /* Telemetry Component */ \
    { \
        .component_id = 2, \
        .read_handler = telemetry_read_handler, \
        .write_handler = telemetry_write_handler, \
        .method_handler = telemetry_method_handler \
    }, \
    /* Nvm Component */ \
    { \
        .component_id = 3, \
        .read_handler = nvm_read_handler, \
        .write_handler = nvm_write_handler, \
        .method_handler = nvm_method_handler \
    } \
};

#endif
