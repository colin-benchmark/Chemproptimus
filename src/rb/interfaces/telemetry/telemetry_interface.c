#include "status.h"
#include "telemetry/telemetry.h"
#include "telemetry/telemetry_attributes.h"
#include "telemetry/telemetry_methods.h"
#include "telemetry/telemetry_callbacks.h"
#include "telemetry/telemetry_instance.h"
#include "telemetry_interface.h"
#include <stdint.h>
#include <string.h>

/**********************************************************
 * Autogenerated code. Don't edit as it'll be overwritten
 *********************************************************/

status_t telemetry_read_handler(
    uint8_t attribute_id,
    uint16_t first,
    uint16_t last,
    uint8_t *output,
    uint8_t output_len,
    uint8_t *bytes_written
) {
    status_t status = STATUS_SUCCESS;
    uint8_t bytes_to_write = 0;

    if (first > last) {
        return STATUS_COMMS_INVALID_ROWS;
    }

    switch (attribute_id) {
        
        case TELEMETRY_ATTRIBUTE_TEMPERATURE_ID:
            if (last >= TELEMETRY_ATTRIBUTE_TEMPERATURE_ROWS) {
                last = TELEMETRY_ATTRIBUTE_TEMPERATURE_ROWS - 1;
            }
            bytes_to_write = sizeof(float) * (last - first + 1);
            if (bytes_to_write > output_len) {
                return STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE;
            }
            /* rows=8 read_callback= */
            memcpy(output, &telemetry_inst.temperature[first], bytes_to_write);
            break;
        
        case TELEMETRY_ATTRIBUTE_CAPACITOR_VOLTAGE_ID:
            bytes_to_write = sizeof(float);
            if (bytes_to_write > output_len) {
                return STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE;
            }
            /* rows= read_callback= */
            memcpy(output, &telemetry_inst.capacitor_voltage, bytes_to_write);
            break;
        
        case TELEMETRY_ATTRIBUTE_SHOTS_ID:
            if (last >= TELEMETRY_ATTRIBUTE_SHOTS_ROWS) {
                last = TELEMETRY_ATTRIBUTE_SHOTS_ROWS - 1;
            }
            bytes_to_write = sizeof(uint32_t) * (last - first + 1);
            if (bytes_to_write > output_len) {
                return STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE;
            }
            /* rows=4 read_callback= */
            memcpy(output, &telemetry_inst.shots[first], bytes_to_write);
            break;
        
        default:
            return STATUS_COMMS_INVALID_ATTRIB_ID;
    }

    *bytes_written = bytes_to_write;
    return status;
}

status_t telemetry_write_handler(
    uint8_t attribute_id,
    uint16_t first,
    uint16_t last,
    uint8_t *input,
    uint8_t input_len
) {
    status_t status = STATUS_SUCCESS;
    uint8_t bytes_to_write = 0;

    if (first > last) {
        return STATUS_COMMS_INVALID_ROWS;
    }

    switch (attribute_id) {
        
        case TELEMETRY_ATTRIBUTE_TEMPERATURE_ID:
            return STATUS_COMMS_READONLY;
            
        case TELEMETRY_ATTRIBUTE_CAPACITOR_VOLTAGE_ID:
            return STATUS_COMMS_READONLY;
            
        case TELEMETRY_ATTRIBUTE_SHOTS_ID:
            return STATUS_COMMS_READONLY;
            
        default:
            return STATUS_COMMS_INVALID_ATTRIB_ID;
    }

    return status;
}

status_t telemetry_method_handler(
    uint8_t method_id,
    uint8_t *input,
    uint8_t input_len
) {
    status_t status = STATUS_ERROR;

    

    return status;
}
