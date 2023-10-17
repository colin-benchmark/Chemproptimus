#include "status.h"

#ifndef EEPROM_METHODS_H
#define EEPROM_METHODS_H

/**********************************************************
 * Autogenerated code. Don't edit as it'll be overwritten
 *********************************************************/

#define EEPROM_METHOD_RESET_ID (0)


#define EEPROM_METHOD_RESET_PARAM_BYTES (0)

/**********************************************************
 * Reset the EEPROM to a set of known working defaults. Requires the correct Codeword to be written in the EEPROM component
 *********************************************************/
status_t eeprom_reset();


#endif
