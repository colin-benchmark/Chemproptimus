#include "unity.h"
#include <stdio.h>

/* Includes for files under test */
#include "component_processor/component_processor.h"
#include "packet_processor/packet.h"
#include "packet_processor/packet_processor.h"
#include "packet_processor/packet_utilities.h"
#include "status.h"

void setUp(void) {
    /* Per test setup */
}

void tearDown(void) {
    /* Per test cleanup */
}

void test_basic_message() {
    uint8_t packet[] = {};
    uint16_t packet_len = sizeof(packet);
    uint8_t tx_buffer[PACKET_BUFFER_SIZE];
    uint8_t tx_len = 0;

    tx_len = process_packet(packet, packet_len, tx_buffer);

    TEST_ASSERT_EQUAL(tx_len, 2);
}