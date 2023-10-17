#include "status.h"
#include <stdint.h>

/**********************************************************
 * Autogenerated code. Don't edit as it'll be overwritten
 *********************************************************/

#ifndef POWER_INTERFACE_H
#define POWER_INTERFACE_H

status_t power_read_handler(
    uint8_t attribute_id,
    uint16_t first,
    uint16_t last,
    uint8_t *output,
    uint8_t output_len,
    uint8_t *bytes_written
);

status_t power_write_handler(
    uint8_t attribute_id,
    uint16_t first,
    uint16_t last,
    uint8_t *input,
    uint8_t input_len
);

status_t power_method_handler(
    uint8_t method_id,
    uint8_t *input,
    uint8_t input_len
);

#endif
