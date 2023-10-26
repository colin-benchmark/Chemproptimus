#include "packet_processor/packet_utilities.h"
#include "packet_processor/packet.h"
#include "status.h"

#include "status.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

uint8_t build_response_packet(status_t status, uint8_t *data, uint8_t data_len, uint8_t *output) {
    /* ensure we've enough room when adding in fields:
     * min packet size inc last_crc_l + last_crc_h + crc_l + crc_h */

    if (data_len > PACKET_BUFFER_SIZE - 2) {
        status = STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE;
        data_len = 0;
    }

    output[0] = (uint8_t)(status & 0xFF);
    output[1] = (uint8_t)(status >> 8);

    if (data_len && data != NULL && status == STATUS_SUCCESS) {
        memcpy(&output[2], data, data_len);
    }

    return data_len + 2; /* status code */
}
