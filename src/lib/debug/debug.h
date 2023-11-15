#ifndef DEBUG_H
#define DEBUG_H

/**
   @file
   Debug and log.
*/

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "config/conf_log.h"
#include "debug/debug_instance.h"

/**
   Debug levels.
*/
typedef enum
{
    LOG_ERROR = 0,  //!< Error
    LOG_WARN = 1,   //!< Warning
    LOG_INFO = 2,   //!< Informational
    LOG_DEBUG = 3,  //!< Debug
} debug_level_t;

/**
   Color and color modifiers.
*/
typedef enum
{
    /* Colors */
    LOG_COLOUR_RESET = 0xF0,
    LOG_COLOUR_BLACK = 0x01,
    LOG_COLOUR_RED = 0x02,
    LOG_COLOUR_GREEN = 0x03,
    LOG_COLOUR_YELLOW = 0x04,
    LOG_COLOUR_BLUE = 0x05,
    LOG_COLOUR_MAGENTA = 0x06,
    LOG_COLOUR_CYAN = 0x07,
    LOG_COLOUR_WHITE = 0x08,
    /* Modifiers */
    LOG_COLOUR_NORMAL = 0x0F,
    LOG_COLOUR_BOLD = 0x10,
    LOG_COLOUR_UNDERLINE = 0x20,
    LOG_COLOUR_BLINK = 0x30,
    LOG_COLOUR_HIDE = 0x40,
} log_color_t;

/** Color mask */
#define LOG_COLOUR_MASK_COLOR 0x0F
/** Color modifier mask */
#define LOG_COLOUR_MASK_MODIFIER 0xF0

/**
   Extract filename component from path
*/
#define BASENAME(_file) ((strrchr(_file, '/') ?: (strrchr(_file, '\\') ?: _file)) + 1)

#if !(__DOXYGEN__)
/* Ensure defines are 'defined' */
#if !defined(LOG_ENABLED)
#define LOG_ENABLED 0
#endif

#if !defined(LOG_LEVEL_DEBUG)
#define LOG_LEVEL_DEBUG 0
#endif

#if !defined(LOG_LEVEL_INFO)
#define LOG_LEVEL_INFO 0
#endif

#if !defined(LOG_LEVEL_WARN)
#define LOG_LEVEL_WARN 0
#endif

#if !defined(LOG_LEVEL_ERROR)
#define LOG_LEVEL_ERROR 0
#endif
#endif  // __DOXYGEN__

/**
 * Log message with specific level.
 * @param level log level
 * @param format log message, printf syntax.
 */
#define debug(sfile, sline, level, format, ...)                   \
    {                                                             \
        if (LOG_ENABLED && debug_inst.enabled[level])             \
            do_debug(sfile, sline, level, format, ##__VA_ARGS__); \
    }

/**
 * Log message with level #LOG_ERROR.
 * @param format log message, printf syntax.
 */
#define log_error(format, ...)                                                \
    {                                                                         \
        if (LOG_LEVEL_ERROR)                                                  \
            debug(__FILE_NAME__, __LINE__, LOG_ERROR, format, ##__VA_ARGS__); \
    }

/**
 * Log message with level #LOG_WARN.
 * @param format log message, printf syntax.
 */
#define log_warn(format, ...)                                                \
    {                                                                        \
        if (LOG_LEVEL_WARN)                                                  \
            debug(__FILE_NAME__, __LINE__, LOG_WARN, format, ##__VA_ARGS__); \
    }

/**
 * Log message with level #LOG_INFO.
 * @param format log message, printf syntax.
 */
#define log_info(format, ...)                                                \
    {                                                                        \
        if (LOG_LEVEL_INFO)                                                  \
            debug(__FILE_NAME__, __LINE__, LOG_INFO, format, ##__VA_ARGS__); \
    }

/**
 * Log message with level #LOG_BUFFER.
 * @param format log message, printf syntax.
 */
#define log_debug(format, ...)                                                \
    {                                                                         \
        if (LOG_LEVEL_DEBUG)                                                  \
            debug(__FILE_NAME__, __LINE__, LOG_DEBUG, format, ##__VA_ARGS__); \
    }

/**
 * Do the actual logging (don't use directly).
 * @note Use the log_<level>() macros instead.
 * @param level log level
 * @param format log message, printf syntax.
 */
void do_debug(const char *sfile, uint16_t sline, debug_level_t level, const char *format, ...)
    __attribute__((format(__printf__, 4, 5)));

/**
 * Toggle debug level on/off
 * @param level Level to toggle
 */
void debug_toggle_level(debug_level_t level);

/**
 * Set debug level
 * @param level Level to set
 * @param value New level value
 */
void debug_set_level(debug_level_t level, bool value);

/**
 * Get current debug level value
 * @param level Level to get
 * @return Level value
 */
int debug_get_level(debug_level_t level);

#endif  // DEBUG_H
