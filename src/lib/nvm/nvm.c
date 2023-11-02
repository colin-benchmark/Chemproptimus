#include "nvm.h"
#include "nvm/nvm_attributes.h"
#include "nvm/nvm_instance.h"
#include "nvm/nvm_methods.h"
#include "status.h"

#include <stdbool.h>
#include <stdint.h>

#include <asf.h>
#include <flash_efc.h>

static uint32_t ul_page_buffer[IFLASH_PAGE_SIZE / sizeof(uint32_t)] = { 0 };

status_t nvm_init() {
    status_t status = STATUS_SUCCESS;
    uint32_t ul_rc;

    printf("Initializing NVM component\b\r");

    /* Initialize flash: 6 wait states for flash writing. */
    ul_rc = flash_init(FLASH_ACCESS_MODE_128, 6);

    if (ul_rc != FLASH_RC_OK) {
        printf("Flash initialization error %lu\n\r", ul_rc);
        status = STATUS_ERROR;
    }

    return status;
}

status_t nvm_reset() {
    status_t status = STATUS_SUCCESS;
    uint32_t ul_rc;
    uint32_t ul_test_page_addr = TEST_PAGE_ADDRESS;

    printf("Flash: Reset\n\r");

    ul_rc = flash_unlock(ul_test_page_addr, ul_test_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
    if (ul_rc != FLASH_RC_OK) {
        printf("Flash Unlock error %lu\n\r", ul_rc);
        status = STATUS_ERROR;
    }

    if (status == STATUS_SUCCESS) {
        ul_rc = flash_erase_sector(ul_test_page_addr);
        if (ul_rc != FLASH_RC_OK) {
            printf("Flash erase error %lu\n\r", ul_rc);
            status = STATUS_ERROR;
        }
    }

    return status;
}

status_t nvm_write() {
    status_t status = STATUS_SUCCESS;
    uint32_t ul_rc;
    uint32_t ul_test_page_addr = TEST_PAGE_ADDRESS;

    printf("Flash: Write\n\r");

    ul_rc = flash_unlock(ul_test_page_addr, ul_test_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
    if (ul_rc != FLASH_RC_OK) {
        printf("Flash Unlock error %lu\n\r", ul_rc);
        status = STATUS_ERROR;
    }

    if (status == STATUS_SUCCESS) {
        ul_page_buffer[0] = 123;
        ul_page_buffer[1] = 456;

        /* The EWP command is not supported for non-8KByte sectors in all devices
	     * SAM4 series, so an erase command is requried before the write operation.
	     */
        ul_rc = flash_erase_sector(ul_test_page_addr);
        if (ul_rc != FLASH_RC_OK) {
            printf("Flash erase error %lu\n\r", ul_rc);
            status = STATUS_ERROR;
        }

        if (status == STATUS_SUCCESS) {
            ul_rc = flash_write(ul_test_page_addr, ul_page_buffer, IFLASH_PAGE_SIZE, 0);

            if (ul_rc != FLASH_RC_OK) {
                printf("Flash programming error %lu\n\r", ul_rc);
                status = STATUS_ERROR;
            }
        }
    }

    if (status == STATUS_SUCCESS) {
        ul_rc = flash_lock(ul_test_page_addr, ul_test_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
        if (ul_rc != FLASH_RC_OK) {
            printf("Flash locking error %lu\n\r", ul_rc);
            status = STATUS_ERROR;
        }
    }

    return status;
}

status_t nvm_read() {
    status_t status = STATUS_SUCCESS;
    uint32_t *pul_test_page = (uint32_t *)TEST_PAGE_ADDRESS;

    printf("Flash: Read\n\r");

    printf("Read: %ld %ld\n\r", pul_test_page[0], pul_test_page[1]);

    return status;
}

status_t nvm_length_read_callback(uint32_t *buf) {
    return STATUS_NOT_IMPLEMENTED;
}