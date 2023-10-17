#ifndef STATUS_H
#define STATUS_H

typedef enum
{
    /* Generic error codes */
    STATUS_SUCCESS = 0x000,
    STATUS_ERROR = 0x001,
    STATUS_BUSY = 0x002,
    STATUS_TIMEOUT = 0x003,
    STATUS_UNSUPPORTED = 0x004,
    STATUS_NOT_IMPLEMENTED = 0x005,
    STATUS_COMMS_LENGHT_ERROR = 0x0100,
    STATUS_COMMS_INVALID_TYPE = 0x0100,
    STATUS_COMMS_CRC_ERROR = 0x0100,
    STATUS_COMMS_TIMEOUT_ERROR = 0x0100,
    STATUS_COMMS_INSUFFICIENT_BUFFER_SPACE = 0x0100,
    STATUS_COMMS_INVALID_INSTANCE_ID = 0x0100,
    STATUS_COMMS_INVALID_ATTRIB_ID = 0x0100,
    STATUS_COMMS_INVALID_ROWS = 0x0100,
    STATUS_COMMS_INCORRECT_INPUT_DATA = 0x0100,
    STATUS_COMMS_INVALID_ADDRESS = 0x0100,
    STATUS_COMMS_INVALID_METHOD_ID = 0x0100,
    STATUS_COMMS_READONLY = 0x0100,
} status_t;

#endif /* STATUS_H */
