#include "status.h"
#include <stdint.h>

#ifndef COMPONENT_PROCESSOR_H
#define COMPONENT_PROCESSOR_H

#define ATTRIBUTE_MAX_HANDLERS 16

typedef status_t (*fn_read_handler)(uint8_t, uint8_t, uint16_t, uint16_t, uint8_t *, uint8_t, uint8_t *);
typedef status_t (*fn_write_handler)(uint8_t, uint8_t, uint16_t, uint16_t, uint8_t *, uint8_t);
typedef status_t (*fn_method_handler)(uint8_t, uint8_t, uint8_t *, uint8_t);

typedef struct _AttributeProcessor
{
    uint8_t component_id;
    uint8_t component_n;
    fn_read_handler read_handler;
    fn_write_handler write_handler;
    fn_method_handler method_handler;
} ComponentProcessor;

status_t component_read_single_attrb(
    uint8_t component_id,
    uint8_t attribute_id,
    uint16_t first_row,
    uint16_t last_row,
    uint8_t *output,
    uint8_t output_len,
    uint8_t *bytes_written
);

status_t component_read_multiple_attrb(
    uint8_t component,
    uint8_t attribute_first,
    uint8_t attribute_last,
    uint8_t *output,
    uint8_t output_len,
    uint8_t *bytes_written
);

status_t component_write_single_attrb(
    uint8_t component_id, uint8_t attribute_id, uint16_t first_row, uint16_t last_row, uint8_t *input, uint8_t input_len
);

status_t component_call_method(uint8_t component_id, uint8_t method_id, uint8_t *input, uint8_t input_len);

void component_processor_init(ComponentProcessor *component_processors, uint8_t n_processors);

#endif
