#include <stdint.h>
#include <stdbool.h>

/**********************************************************
 * Autogenerated code. Don't edit as it'll be overwritten
 *********************************************************/

#ifndef DEVICE_ATTRIBUTES_H
#define DEVICE_ATTRIBUTES_H

#define DEVICE_ATTRIBUTE_VERSION_ROWS (3)
#define DEVICE_ATTRIBUTE_MANUFACTURER_ROWS (9)
#define DEVICE_ATTRIBUTE_SERIAL_NUMBER_ROWS (8)
#define DEVICE_ATTRIBUTE_BUILD_ROWS (0)
#define DEVICE_ATTRIBUTE_BOOTCOUNTER_ROWS (0)
#define DEVICE_ATTRIBUTE_STATUS_ROWS (0)
#define DEVICE_ATTRIBUTE_LAST_ERROR_ROWS (0)
#define DEVICE_ATTRIBUTE_LOG_LEVEL_ROWS (0)
#define DEVICE_ATTRIBUTE_CHECKSUM_ROWS (0)


#define DEVICE_ATTRIBUTE_VERSION_ID (0)
#define DEVICE_ATTRIBUTE_MANUFACTURER_ID (1)
#define DEVICE_ATTRIBUTE_SERIAL_NUMBER_ID (2)
#define DEVICE_ATTRIBUTE_BUILD_ID (3)
#define DEVICE_ATTRIBUTE_BOOTCOUNTER_ID (4)
#define DEVICE_ATTRIBUTE_STATUS_ID (5)
#define DEVICE_ATTRIBUTE_LAST_ERROR_ID (6)
#define DEVICE_ATTRIBUTE_LOG_LEVEL_ID (7)
#define DEVICE_ATTRIBUTE_CHECKSUM_ID (8)


typedef struct _device_attributes {
    uint8_t version[DEVICE_ATTRIBUTE_VERSION_ROWS]; /* Major, minor and patch version number */
    uint8_t manufacturer[DEVICE_ATTRIBUTE_MANUFACTURER_ROWS]; /* Will return benchmark */
    uint8_t serial_number[DEVICE_ATTRIBUTE_SERIAL_NUMBER_ROWS]; /* The serial number of the device. Can only be written with the correct Codeword written to the EEPROM component */
    uint32_t build; /* SHA of current commit at build */
    uint16_t bootcounter; /* Number of times this device has been booted */
    uint16_t status; /* Bit-code indication of device health */
    uint8_t last_error; /* The last error code generated by an operation made on the device. Cleared after reading. */
    uint8_t log_level; /* Enable verbose debugging of the platform. Primarily this will enable outputting messages via the secondary comms port. This may also mean enabling certain features not required for nominal operations. The level will define the verbosity of this output with 0 meaning NO DEBUG */
    uint32_t checksum; /* On boot generate a checksum based on the firmware loaded to aid in identifying its version if other tests fail. Also provides a method of detecting firmware image corruption */
} device_attributes;



#endif
