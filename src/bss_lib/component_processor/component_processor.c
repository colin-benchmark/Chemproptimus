#include "component_processor.h"
#include "comms_status.h"
#include "device_registers.h"
#include "null.h"
#include "packet_processor/packet.h"
#include "status.h"
#include <stdint.h>

static ComponentProcessor *processors;
static uint8_t processors_len;

/* TODO: Can refactor this to just */
ComponentProcessor *getcomponent_processor(uint8_t component_id) {
    uint8_t i = 0;
    ComponentProcessor *processor = NULL;

    if (component_id < processors_len) {
        processor = &processors[component_id];
    }

    return processor;
}

status_t component_read_single_attrb(
    uint8_t component_id,
    uint8_t attribute_id,
    uint16_t first_row,
    uint16_t last_row,
    uint8_t *output,
    uint8_t output_len,
    uint8_t *bytes_written
) {
    ComponentProcessor *processor = getcomponent_processor(component_id);
    status_t status = STATUS_UNSUPPORTED;

    *bytes_written = 0;

    if (processor != NULL && processor->read_handler != NULL) {
        status = processor->read_handler(
            processor->component_n, attribute_id, first_row, last_row, output, output_len, bytes_written
        );
    } else {
        status = COMMS_STATUS_INVALID_INSTANCE_ID;
    }

    return status;
}

status_t component_read_multiple_attrb(
    uint8_t component_id,
    uint8_t attribute_first,
    uint8_t attribute_last,
    uint8_t *output,
    uint8_t output_len,
    uint8_t *bytes_written
) {
    status_t status = STATUS_SUCCESS;
    uint8_t attrib_id;
    uint8_t attribute_bytes_written = 0;

    *(bytes_written) = 0;

    for (attrib_id = attribute_first; attrib_id <= attribute_last; attrib_id++) {
        status = component_read_single_attrb(
            component_id,
            attrib_id,
            0,
            PACKET_ALL_ROWS,
            &output[*bytes_written],
            (output_len - *bytes_written),
            &attribute_bytes_written
        );

        *bytes_written += attribute_bytes_written;

        if (status != STATUS_SUCCESS) {
            break;
        }
    }

    return status;
}

status_t component_write_single_attrb(
    uint8_t component_id, uint8_t attribute_id, uint16_t first_row, uint16_t last_row, uint8_t *input, uint8_t input_len
) {
    ComponentProcessor *processor = getcomponent_processor(component_id);
    status_t status = STATUS_UNSUPPORTED;

    if (processor != NULL && processor->write_handler != NULL) {
        status = processor->write_handler(processor->component_n, attribute_id, first_row, last_row, input, input_len);
    } else {
        status = COMMS_STATUS_INVALID_INSTANCE_ID;
    }

    return status;
}

status_t component_call_method(uint8_t component_id, uint8_t method_id, uint8_t *input, uint8_t input_len) {
    ComponentProcessor *processor = getcomponent_processor(component_id);
    status_t status = STATUS_UNSUPPORTED;

    if (processor != NULL && processor->method_handler != NULL) {
        status = processor->method_handler(processor->component_n, method_id, input, input_len);
    } else {
        status = COMMS_STATUS_INVALID_INSTANCE_ID;
    }

    return status;
}

void component_processor_init(ComponentProcessor *component_processors, uint8_t n_processors) {
    if (component_processors != NULL && n_processors) {
        processors = component_processors;
        processors_len = n_processors;
    } else {
        /* bad data when initialising the attribute processor */
        DEV_ASSERT(0);
    }
}
