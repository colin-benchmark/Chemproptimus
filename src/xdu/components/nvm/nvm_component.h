#include "status.h"
#include <stdint.h>
#include "nvm/nvm_attributes.h"
#include "nvm_methods.h"

/**********************************************************
 * Autogenerated code. Don't edit as it'll be overwritten
 *
 * All functions described need implemented by the
 * developer as part of their own codebase
 *********************************************************/

#ifndef NVM_COMPONENT_H
#define NVM_COMPONENT_H

/**********************************************************
 * Initialise the nvm component
 *********************************************************/
status_t nvm_init();

/**********************************************************
 * Reset the EEPROM to a set of known working defaults. Requires the correct Codeword to be written in the EEPROM component
 *********************************************************/
status_t nvm_reset();

/**********************************************************
 * Write cached copy of NVM data to Flash
 *********************************************************/
status_t nvm_store();

/**********************************************************
 * Read NVM data in Flash to cache
 *********************************************************/
status_t nvm_load();


#endif
