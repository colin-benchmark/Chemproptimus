#include "debug/debug.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "debug/debug_instance.h"

void debug_sys_set_color(log_color_t color) {
    unsigned int color_code, modifier_code;
    switch (color & LOG_COLOUR_MASK_COLOR) {
        case LOG_COLOUR_BLACK:
            color_code = 30;
            break;
        case LOG_COLOUR_RED:
            color_code = 31;
            break;
        case LOG_COLOUR_GREEN:
            color_code = 32;
            break;
        case LOG_COLOUR_YELLOW:
            color_code = 33;
            break;
        case LOG_COLOUR_BLUE:
            color_code = 34;
            break;
        case LOG_COLOUR_MAGENTA:
            color_code = 35;
            break;
        case LOG_COLOUR_CYAN:
            color_code = 36;
            break;
        case LOG_COLOUR_WHITE:
            color_code = 37;
            break;
        case LOG_COLOUR_RESET:
        default:
            color_code = 0;
            break;
    }

    switch (color & LOG_COLOUR_MASK_MODIFIER) {
        case LOG_COLOUR_BOLD:
            modifier_code = 1;
            break;
        case LOG_COLOUR_UNDERLINE:
            modifier_code = 2;
            break;
        case LOG_COLOUR_BLINK:
            modifier_code = 3;
            break;
        case LOG_COLOUR_HIDE:
            modifier_code = 4;
            break;
        case LOG_COLOUR_NORMAL:
        default:
            modifier_code = 0;
            break;
    }

    printf("\033[%u;%um", modifier_code, color_code);
}

void do_debug(debug_level_t level, const char *format, ...) {
    int color = LOG_COLOUR_RESET;
    va_list args;

    /* Don't print anything if log level is disabled */
    if (level > LOG_DEBUG || !debug_inst.enabled[level])
        return;

    switch (level) {
        case LOG_INFO:
            color = LOG_COLOUR_GREEN | LOG_COLOUR_BOLD;
            break;
        case LOG_ERROR:
            color = LOG_COLOUR_RED | LOG_COLOUR_BOLD;
            break;
        case LOG_WARN:
            color = LOG_COLOUR_YELLOW | LOG_COLOUR_BOLD;
            break;
        case LOG_DEBUG:
            color = LOG_COLOUR_CYAN;
            break;
        default:
            return;
    }

    va_start(args, format);

    debug_sys_set_color(color);
    vprintf(format, args);
    printf("\r\n");
    debug_sys_set_color(LOG_COLOUR_RESET);

    va_end(args);
}

void debug_set_level(debug_level_t level, bool value) {
    if (level <= LOG_DEBUG) {
        debug_inst.enabled[level] = value;
    }
}

int debug_get_level(debug_level_t level) {
    if (level <= LOG_DEBUG) {
        return debug_inst.enabled[level];
    }
    return 0;
}

void debug_toggle_level(debug_level_t level) {
    if (level <= LOG_DEBUG) {
        debug_inst.enabled[level] = (debug_inst.enabled[level]) ? false : true;
    }
}
