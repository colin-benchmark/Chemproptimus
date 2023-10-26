#include "status.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef PACKET_UTILITIES_H
#define PACKET_UTILITIES_H

uint8_t build_response_packet(status_t status, uint8_t *data, uint8_t tx_len, uint8_t *output);

#endif
