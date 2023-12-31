#include <stdint.h>
#include <stdbool.h>

/**********************************************************
 * Autogenerated code. Don't edit as it'll be overwritten
 *********************************************************/

#ifndef NVM_ATTRIBUTES_H
#define NVM_ATTRIBUTES_H

#define NVM_ATTRIBUTE_LENGTH_ROWS (0)
#define NVM_ATTRIBUTE_VALID_ROWS (0)
#define NVM_ATTRIBUTE_UPDATE_REQUIRED_ROWS (0)


#define NVM_ATTRIBUTE_LENGTH_ID (0)
#define NVM_ATTRIBUTE_VALID_ID (1)
#define NVM_ATTRIBUTE_UPDATE_REQUIRED_ID (2)


typedef struct _nvm_attributes {
    uint32_t length; /* Number of bytes used by NVM storage */
    bool valid; /* Confirm the Flash has been initialised for NVM data */
    bool update_required; /* True if there&#39;s a difference between the NVM contents and component values */
} nvm_attributes;



#endif
