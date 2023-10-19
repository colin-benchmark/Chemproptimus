#include "packet_processor.h"
#include "component_processor/component_processor.h"
#include "packet.h"
#include "packet_utilities.h"
#include "status.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

uint8_t process_packet(uint8_t *packet, uint16_t packet_len, uint8_t *tx_buffer, uint8_t tx_len) {
    uint8_t data_bytes_written = 0;
    status_t status = STATUS_SUCCESS;
    uint16_t first_row = 0;
    uint16_t last_row = 0;
    uint8_t data[PACKET_BUFFER_SIZE];

    if (packet != NULL) {
        switch (packet[PACKET_BYTE_POS_TYPE]) {
            case PACKET_TYPE_READ_SINGLETON:
                if (packet_len == PACKET_TYPE_READ_SINGLETON_LENGTH) {
                    status = component_read_single_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        0,
                        0,
                        data,
                        PACKET_BUFFER_SIZE,
                        &data_bytes_written
                    );
                } else {
                    status = STATUS_COMMS_INCORRECT_INPUT_DATA;
                }
                break;

            case PACKET_TYPE_READ_MULTI_ROW:
                if (packet_len == PACKET_TYPE_READ_MULTI_ROW_LENGTH) {
                    first_row = (packet[PACKET_BYTE_POS_ROW_FIRST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_FIRST];
                    last_row = (packet[PACKET_BYTE_POS_ROW_LAST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_LAST];

                    status = component_read_single_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        first_row,
                        last_row,
                        data,
                        PACKET_BUFFER_SIZE,
                        &data_bytes_written
                    );
                } else {
                    status = STATUS_COMMS_INCORRECT_INPUT_DATA;
                }
                break;

            case PACKET_TYPE_READ_MULTI_ATTRIB:
                if (packet_len == PACKET_TYPE_READ_MULTI_ATTRIB_LENGTH) {
                    status = component_read_multiple_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE_LAST],
                        data,
                        PACKET_BUFFER_SIZE,
                        &data_bytes_written
                    );
                } else {
                    status = STATUS_COMMS_INCORRECT_INPUT_DATA;
                }
                break;

            case PACKET_TYPE_WRITE_SINGLETON:

                if (packet_len >= PACKET_TYPE_WRITE_SINGLETON_LENGTH_MINIMUM) {
                    first_row = (packet[PACKET_BYTE_POS_ROW_FIRST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_FIRST];
                    last_row = (packet[PACKET_BYTE_POS_ROW_LAST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_LAST];

                    status = component_write_single_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        0,
                        0,
                        &packet[PACKET_BYTE_WRITE_SINGLETON_DATA],
                        packet_len - 2 /* component and attr fields */
                    );

                } else {
                    status = STATUS_COMMS_INCORRECT_INPUT_DATA;
                }

                break;

            case PACKET_TYPE_WRITE_MULTI_ROW:
                if (packet_len >= PACKET_TYPE_WRITE_MULTI_ROW_LENGTH_MINIMUM) {
                    first_row = (packet[PACKET_BYTE_POS_ROW_FIRST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_FIRST];
                    last_row = (packet[PACKET_BYTE_POS_ROW_LAST + 1] << 8) | packet[PACKET_BYTE_POS_ROW_LAST];

                    status = component_write_single_attrb(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_ATTRIBUTE],
                        first_row,
                        last_row,
                        &packet[PACKET_BYTE_WRITE_MULTI_ROW_DATA],
                        packet_len - 6 /* component, attr and 4 row fields */
                    );
                } else {
                    status = STATUS_COMMS_INCORRECT_INPUT_DATA;
                }

                break;

            case PACKET_TYPE_EXECUTE:
                if (packet_len >= PACKET_TYPE_EXECUTE_LENGTH_MINIMUM) {
                    status = component_call_method(
                        packet[PACKET_BYTE_POS_INSTANCE],
                        packet[PACKET_BYTE_POS_METHOD],
                        &packet[PACKET_BYTE_METHOD_DATA],
                        packet_len - 2 /* component and method fields */
                    );
                } else {
                    status = STATUS_COMMS_INCORRECT_INPUT_DATA;
                }
                break;

            default:
                break;
                /* do nothing */
        }
    }

    return build_response_packet(status, data, data_bytes_written, tx_buffer);
}
