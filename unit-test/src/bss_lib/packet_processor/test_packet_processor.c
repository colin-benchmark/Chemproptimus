#include "unity.h"
#include <stdio.h>

/* Includes for files under test */
#include "component_processor/component_processor.h"
#include "packet_processor/packet.h"
#include "packet_processor/packet_processor.h"
#include "packet_processor/packet_utilities.h"
#include "status.h"

#define GET_PACKET_STATUS(buf) ((status_t)((buf[1] << 8) | buf[0]))

void setUp(void) {
    /* Per test setup */
}

void tearDown(void) {
    /* Per test cleanup */
}

void test_EmptyMessage() {
    uint8_t packet[] = {};
    uint8_t tx_buffer[PACKET_BUFFER_SIZE];
    uint8_t tx_len = 0;

    tx_len = process_packet(packet, sizeof(packet), tx_buffer);

    TEST_ASSERT_EQUAL(2, tx_len); /* Only contains error message (16 bits) */
    TEST_ASSERT_EQUAL(STATUS_COMMS_INCORRECT_INPUT_DATA, GET_PACKET_STATUS(tx_buffer));
}