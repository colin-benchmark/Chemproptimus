/*
 * conf_csp.h
 *
 * Created: 17.03.2016 22:58:13
 *  Author: Admin
 */

#ifndef CONF_CSP_H_
#define CONF_CSP_H_

#define GIT_REV ""
#define CSP_FREERTOS 1
#define FREERTOS_VERSION_NR 8
/* #undef CSP_USE_RDP */
/* #undef CSP_USE_HMAC */
/* #undef CSP_USE_XTEA */
/* #undef CSP_USE_PROMISC */
/* #undef CSP_USE_QOS */
/* #undef CSP_BIG_ENDIAN */
#define CSP_USE_DEBUG_COLOR 0
/* #undef CSP_POSIX */
/* #undef CSP_WINDOWS */
/* #undef CSP_MACOSX */
#define CSP_DEBUG 1
#define CSP_VERBOSE 1
#define CSP_USE_RDP 1
#define CSP_USE_CRC32 1
#define CSP_USE_HMAC 1
#define CSP_USE_XTEA 1
/* #undef CSP_USE_PROMISC */
#define CSP_USE_QOS 1
#define CSP_CONN_MAX 10
#define CSP_CONN_QUEUE_LENGTH 100
#define CSP_FIFO_INPUT 30
#define CSP_MAX_BIND_PORT 31
#define CSP_RDP_MAX_WINDOW 20
#define CSP_TRANSACTION_SO 0
#define CSP_CONNECTION_SO \
    CSP_TRANSACTION_SO  // The code uses CSP_CONNECTION_SO, CSP_TRANSACTION is never referenced by code. i suspect the define got a namechange between the build and code version.
#define CSP_LOG_LEVEL_DEBUG 1
#define CSP_LOG_LEVEL_INFO 1
#define CSP_LOG_LEVEL_WARN 1
#define CSP_LOG_LEVEL_ERROR 1
#define CSP_LITTLE_ENDIAN 1
/* #undef CSP_BIG_ENDIAN */
#define CSP_HAVE_STDBOOL_H 1

#define CSP_ADDRESS 0x10
#endif /* CONF_CSP_H_ */