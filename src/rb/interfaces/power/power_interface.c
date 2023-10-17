#include "status.h"
#include "power/power.h"
#include "power/power_attributes.h"
#include "power/power_methods.h"
#include "power/power_instance.h"
#include "power_interface.h"
#include <stdint.h>
#include <string.h>

/**********************************************************
 * Autogenerated code. Don't edit as it'll be overwritten
 *********************************************************/

status_t power_read_handler(
    uint8_t attribute_id,
    uint16_t first,
    uint16_t last,
    uint8_t *output,
    uint8_t output_len,
    uint8_t *bytes_written
) {
    uint8_t bytes_to_write = 0;

    if (first > last) {
        return STATUS_COMMS_INVALID_ROWS;
    }

    switch (attribute_id) {
        
        case POWER_ATTRIBUTE_PPU_STATUS_ID:
            bytes_to_write = sizeof(bool);
            if (bytes_to_write > output_len) {
                return STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE;
            }
            memcpy(output, &power_inst.ppu_status, bytes_to_write);
            break;
        
        case POWER_ATTRIBUTE_PPU_FREQUENCY_ID:
            bytes_to_write = sizeof(uint16_t);
            if (bytes_to_write > output_len) {
                return STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE;
            }
            memcpy(output, &power_inst.ppu_frequency, bytes_to_write);
            break;
        
        case POWER_ATTRIBUTE_PPU_DUTY_CYCLE_ID:
            bytes_to_write = sizeof(uint8_t);
            if (bytes_to_write > output_len) {
                return STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE;
            }
            memcpy(output, &power_inst.ppu_duty_cycle, bytes_to_write);
            break;
        
        case POWER_ATTRIBUTE_BUCKBOOST_STATUS_ID:
            bytes_to_write = sizeof(bool);
            if (bytes_to_write > output_len) {
                return STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE;
            }
            memcpy(output, &power_inst.buckboost_status, bytes_to_write);
            break;
        
        case POWER_ATTRIBUTE_CURRENT_LIMIT_ID:
            bytes_to_write = sizeof(uint8_t);
            if (bytes_to_write > output_len) {
                return STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE;
            }
            memcpy(output, &power_inst.current_limit, bytes_to_write);
            break;
        
        default:
            return STATUS_COMMS_INVALID_ATTRIB_ID;
    }

    *bytes_written = bytes_to_write;
    return STATUS_SUCCESS;
}

status_t power_write_handler(
    uint8_t attribute_id,
    uint16_t first,
    uint16_t last,
    uint8_t *input,
    uint8_t input_len
) {
    uint8_t bytes_to_write = 0;

    if (first > last) {
        return STATUS_COMMS_INVALID_ROWS;
    }

    switch (attribute_id) {
        
        case POWER_ATTRIBUTE_PPU_STATUS_ID:
            return STATUS_COMMS_READONLY;
            
        case POWER_ATTRIBUTE_PPU_FREQUENCY_ID:
            bytes_to_write = sizeof(uint16_t);
            if (bytes_to_write != input_len) {
                return STATUS_COMMS_INCORRECT_INPUT_DATA;
            }
            memcpy(&power_inst.ppu_frequency, input, bytes_to_write);
            break;
            
        case POWER_ATTRIBUTE_PPU_DUTY_CYCLE_ID:
            bytes_to_write = sizeof(uint8_t);
            if (bytes_to_write != input_len) {
                return STATUS_COMMS_INCORRECT_INPUT_DATA;
            }
            memcpy(&power_inst.ppu_duty_cycle, input, bytes_to_write);
            break;
            
        case POWER_ATTRIBUTE_BUCKBOOST_STATUS_ID:
            return STATUS_COMMS_READONLY;
            
        case POWER_ATTRIBUTE_CURRENT_LIMIT_ID:
            bytes_to_write = sizeof(uint8_t);
            if (bytes_to_write != input_len) {
                return STATUS_COMMS_INCORRECT_INPUT_DATA;
            }
            memcpy(&power_inst.current_limit, input, bytes_to_write);
            break;
            
        default:
            return STATUS_COMMS_INVALID_ATTRIB_ID;
    }

    return STATUS_SUCCESS;
}

status_t power_method_handler(
    uint8_t method_id,
    uint8_t *input,
    uint8_t input_len
) {
    status_t status = STATUS_ERROR;

    switch (method_id) {
        
        case POWER_METHOD_SET_PPU_ID:
            if (input_len != POWER_METHOD_SET_PPU_PARAM_BYTES) {
                return STATUS_COMMS_INCORRECT_INPUT_DATA;
            }
            struct __attribute__((__packed__)) _power_set_ppu_parameters {
                bool enabled;
            } power_set_ppu_parameters;
            memcpy(&power_set_ppu_parameters, input, input_len);

            status = power_set_ppu(
                power_set_ppu_parameters.enabled
            );
            break;
            
        case POWER_METHOD_SET_BUCKBOOST_ID:
            if (input_len != POWER_METHOD_SET_BUCKBOOST_PARAM_BYTES) {
                return STATUS_COMMS_INCORRECT_INPUT_DATA;
            }
            struct __attribute__((__packed__)) _power_set_buckboost_parameters {
                bool enabled;
            } power_set_buckboost_parameters;
            memcpy(&power_set_buckboost_parameters, input, input_len);

            status = power_set_buckboost(
                power_set_buckboost_parameters.enabled
            );
            break;
            
        default:
            status = STATUS_COMMS_INVALID_METHOD_ID;
    }

    return status;
}
