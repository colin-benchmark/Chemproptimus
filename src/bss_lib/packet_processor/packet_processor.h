#include <stdint.h>

#ifndef PACKET_PROCESSOR_H
#define PACKET_PROCESSOR_H

void packet_processor_init();
void process_packet(uint8_t *packet);

#endif
