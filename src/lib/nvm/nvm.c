#include "nvm.h"
#include "config/conf_tasks.h"
#include "nvm/nvm_attributes.h"
#include "nvm/nvm_instance.h"
#include "nvm/nvm_methods.h"
#include "status.h"

#include "nvm/nvm_cache.h"
#include "nvm/nvm_struct.h"

#include "debug/debug.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <asf.h>
#include <flash_efc.h>

#define TASK_NVM_STORE_STACK_SIZE (2048 / sizeof(portSTACK_TYPE))
#define TASK_NVM_STORE_PERIOD_MS (1000 / portTICK_PERIOD_MS)

status_t nvm_to_cache(nvm_cache_t *cache) {
    status_t status = STATUS_SUCCESS;
    uint32_t *nvm_page = (uint32_t *)NVM_PAGE_ADDRESS;
    uint32_t buf[2 + sizeof(nvm_cache_t)] = { 0 };

    if (2 + sizeof(nvm_cache_t) <= IFLASH_PAGE_SIZE) {
        memcpy(buf, nvm_page, 2 + sizeof(nvm_cache_t));
        memcpy(cache, &buf[NVM_DATA_OFFSET], sizeof(nvm_cache_t));
    } else {
        log_warn("Flash page too small for persistent data");
        status = STATUS_ERROR;
    }

    return status;
}

bool nvm_valid() {
    uint32_t *nvm_page = (uint32_t *)NVM_PAGE_ADDRESS;
    return (nvm_page[0] == sizeof(nvm_cache_t) && nvm_page[1 + sizeof(nvm_cache_t)] == NVM_END_CODEWORD);
}

bool nvm_update_required() {
    status_t status = STATUS_SUCCESS;
    bool update_required = true;
    int diff;

    nvm_cache_t nvm_cache;
    nvm_cache_t inst_cache;

    status = nvm_to_cache(&nvm_cache);

    if (status == STATUS_SUCCESS) {
        status = nvm_instance_to_cache(&inst_cache);
    }

    if (status == STATUS_SUCCESS) {
        diff = memcmp(&nvm_cache, &inst_cache, sizeof(nvm_cache_t));
        update_required = (0 != diff);
    }

    return update_required;
}

/***********************************************************
 * Tasks
 ***********************************************************/

static void nvm_store_task(void *pvParameters) {
    while (1) {
        if (nvm_valid() && nvm_update_required()) {
            (void)nvm_store();
        }
        vTaskDelay(TASK_NVM_STORE_PERIOD_MS);
    }
}

status_t nvm_init() {
    status_t status = STATUS_SUCCESS;
    uint32_t ul_rc;

    log_info("Initializing NVM component\b\r");

    /* Initialize flash: 6 wait states for flash writing. */
    ul_rc = flash_init(FLASH_ACCESS_MODE_128, 6);

    if (ul_rc != FLASH_RC_OK) {
        log_warn("Flash initialization error %lu\n\r", ul_rc);
        status = STATUS_ERROR;
    }

    if (!nvm_valid()) {
        log_warn("Flash NVM region does not contain valid data. Please run nvm.reset() "
                 "to clear and initialise the NVM region");
        status = STATUS_ERROR;
    } else {
        status = nvm_load();
    }

    if (xTaskCreate(nvm_store_task, "CSP Server", TASK_NVM_STORE_STACK_SIZE, NULL, TASK_NVM_STORE_PRIORITY, NULL)
        != pdPASS) {
        log_warn("Failed to create NVM Store task\r\n");
    }

    return status;
}

status_t nvm_write(const void *data, size_t len) {
    status_t status = STATUS_SUCCESS;

    uint32_t ul_rc;
    uint32_t ul_test_page_addr = NVM_PAGE_ADDRESS;
    uint32_t ul_page_buffer[IFLASH_PAGE_SIZE / sizeof(uint32_t)] = { 0 };

    if ((len + 2) > IFLASH_PAGE_SIZE) {
        log_warn("Flash page too small for persistent data");
        status = STATUS_ERROR;
    }

    if (status == STATUS_SUCCESS) {
        ul_rc = flash_unlock(ul_test_page_addr, ul_test_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
        if (ul_rc != FLASH_RC_OK) {
            log_warn("Flash Unlock error %lu\n\r", ul_rc);
            status = STATUS_ERROR;
        }
    }

    if (status == STATUS_SUCCESS) {
        /* The EWP command is not supported for non-8KByte sectors in all devices
	     * SAM4 series, so an erase command is requried before the write operation.
	     */
        ul_rc = flash_erase_sector(ul_test_page_addr);
        if (ul_rc != FLASH_RC_OK) {
            log_warn("Flash erase error %lu\n\r", ul_rc);
            status = STATUS_ERROR;
        }

        if (status == STATUS_SUCCESS) {
            ul_page_buffer[0] = sizeof(nvm_cache_t);
            ul_page_buffer[sizeof(nvm_cache_t) + 1] = NVM_END_CODEWORD;
            memcpy(&ul_page_buffer[1], data, len);
            ul_rc = flash_write(ul_test_page_addr, ul_page_buffer, len + 2, 0);

            if (ul_rc != FLASH_RC_OK) {
                log_warn("Flash programming error %lu\n\r", ul_rc);
                status = STATUS_ERROR;
            }
        }
    }

    if (status == STATUS_SUCCESS) {
        ul_rc = flash_lock(ul_test_page_addr, ul_test_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
        if (ul_rc != FLASH_RC_OK) {
            log_warn("Flash locking error %lu\n\r", ul_rc);
            status = STATUS_ERROR;
        }
    }
}

status_t nvm_store() {
    status_t status = STATUS_SUCCESS;

    log_info("Flash: Store\n\r");

    nvm_cache_t cache;

    if (sizeof(nvm_cache_t) <= IFLASH_PAGE_SIZE) {
        nvm_instance_to_cache(&cache);
        nvm_write(&cache, sizeof(nvm_cache_t));
    } else {
        log_warn("Flash page too small for persistent data");
        status = STATUS_ERROR;
    }

    return status;
}

status_t nvm_load() {
    status_t status = STATUS_SUCCESS;
    uint32_t *nvm_page = (uint32_t *)NVM_PAGE_ADDRESS;
    nvm_cache_t cache;

    log_info("Flash: Load\n\r");
    status = nvm_to_cache(&cache);

    if (status == STATUS_SUCCESS) {
        nvm_cache_to_instance(&cache);
    }

    return status;
}

status_t nvm_reset() {
    status_t status = STATUS_SUCCESS;
    uint32_t ul_rc;
    uint32_t ul_test_page_addr = NVM_PAGE_ADDRESS;
    uint32_t buf[2 + sizeof(nvm_cache_t)] = { 0 };

    log_info("Flash: Reset\n\r");

    ul_rc = flash_unlock(ul_test_page_addr, ul_test_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
    if (ul_rc != FLASH_RC_OK) {
        log_warn("Flash Unlock error %lu\n\r", ul_rc);
        status = STATUS_ERROR;
    }

    if (status == STATUS_SUCCESS) {
        ul_rc = flash_erase_sector(ul_test_page_addr);
        if (ul_rc != FLASH_RC_OK) {
            log_warn("Flash erase error %lu\n\r", ul_rc);
            status = STATUS_ERROR;
        }
    }

    if (status == STATUS_SUCCESS) {
        buf[0] = sizeof(nvm_cache_t);
        buf[1 + sizeof(nvm_cache_t)] = NVM_END_CODEWORD;
        status = nvm_write(buf, sizeof(buf));
    }

    return status;
}

status_t nvm_length_read_callback(uint32_t *buf) {
    *buf = (uint32_t)sizeof(nvm_cache_t);
    return STATUS_SUCCESS;
}

status_t nvm_valid_read_callback(bool *buf) {
    *buf = nvm_valid();
    return STATUS_SUCCESS;
}

status_t nvm_update_required_read_callback(bool *buf) {
    *buf = nvm_update_required();
    return STATUS_SUCCESS;
}