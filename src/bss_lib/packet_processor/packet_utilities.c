#include "packet_processor/packet_utilities.h"
#include "packet_processor/packet.h"
#include "status.h"

#include "status.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

uint8_t build_response_packet(status_t status, uint8_t *data, uint8_t tx_len, uint8_t *output) {
    /* ensure we've enough room when adding in fields:
     * min packet size inc last_crc_l + last_crc_h + crc_l + crc_h */
    assert(tx_len < PACKET_BUFFER_SIZE);

    output[0] = (uint8_t)(status & 0xFF);
    output[1] = (uint8_t)(status >> 8);
    output[2] = tx_len;

    if (tx_len && data != NULL && status == STATUS_SUCCESS) {
        memcpy(&output[3], data, tx_len);
    }

    return tx_len + 2; /* status code + data bytes */
}
