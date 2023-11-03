#include <status.h>

#ifndef NVM_H
#define NVM_H

/* Test page start address. */
#define NVM_PAGE_ADDRESS (IFLASH_ADDR + IFLASH_SIZE - IFLASH_PAGE_SIZE * 4)
#define NVM_DATA_OFFSET (1)
#define NVM_END_CODEWORD (0x1A2B3C4D)

status_t nvm_init();

#endif