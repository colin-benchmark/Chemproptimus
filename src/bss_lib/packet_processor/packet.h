#ifndef PACKET_H
#define PACKET_H

#define PACKET_BUFFER_SIZE 255U

#define PACKET_MINIMUM_TOTAL_SIZE 6
#define PACKET_MAXIMUM_SAFE_PAYLOAD (PACKET_BUFFER_SIZE - 11) /* 11 to account for worst case packet header/footer */
#define PACKET_STOP_BYTE 0xFF

#define PACKET_BYTE_POS_TYPE 0
#define PACKET_BYTE_POS_INSTANCE 1
#define PACKET_BYTE_POS_METHOD 2
#define PACKET_BYTE_POS_ATTRIBUTE 2
#define PACKET_BYTE_POS_ATTRIBUTE_LAST 3
#define PACKET_BYTE_POS_ROW_FIRST 3
#define PACKET_BYTE_POS_ROW_LAST 5
#define PACKET_BYTE_WRITE_SINGLETON_DATA 3
#define PACKET_BYTE_WRITE_MULTI_ROW_DATA 7
#define PACKET_BYTE_METHOD_DATA 3

#define PACKET_ALL_ROWS 0xFF

enum
{
    PACKET_TYPE_READ_SINGLETON = 0x00,
    PACKET_TYPE_READ_MULTI_ROW = 0x01,
    PACKET_TYPE_READ_MULTI_ATTRIB = 0x02,
    PACKET_TYPE_WRITE_SINGLETON = 0x10,
    PACKET_TYPE_WRITE_MULTI_ROW = 0x11,
    PACKET_TYPE_EXECUTE = 0x20,
    PACKET_TYPE_N
};

#define PACKET_TYPE_READ_SINGLETON_LENGTH 3
#define PACKET_TYPE_READ_MULTI_ROW_LENGTH 7
#define PACKET_TYPE_READ_MULTI_ATTRIB_LENGTH 4
#define PACKET_TYPE_WRITE_SINGLETON_LENGTH_MINIMUM 4
#define PACKET_TYPE_WRITE_MULTI_ROW_LENGTH_MINIMUM 8
#define PACKET_TYPE_EXECUTE_LENGTH_MINIMUM 3

#endif
