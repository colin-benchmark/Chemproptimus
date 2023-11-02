#include <status.h>

#ifndef NVM_H
#define NVM_H

#define NVM_ADDR (0x007F6000u)
#define NVM_LEN (0x0000A000u)

#define NVM_BOOTCOUNTER (NVM_ADDR + 0)

/* Test page start address. */
#define TEST_PAGE_ADDRESS (IFLASH_ADDR + IFLASH_SIZE - IFLASH_PAGE_SIZE * 4)

status_t nvm_init();

#endif