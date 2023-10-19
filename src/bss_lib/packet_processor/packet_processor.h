#include <stdint.h>

#ifndef PACKET_PROCESSOR_H
#define PACKET_PROCESSOR_H

void packet_processor_init();
uint8_t process_packet(uint8_t *packet, uint16_t packet_len, uint8_t *tx_buffer, uint8_t tx_len);

#endif
