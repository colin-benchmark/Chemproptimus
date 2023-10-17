#include <stdint.h>
#include <stdbool.h>

/**********************************************************
 * Autogenerated code. Don't edit as it'll be overwritten
 *********************************************************/

#ifndef POWER_ATTRIBUTES_H
#define POWER_ATTRIBUTES_H

#define POWER_ATTRIBUTE_PPU_STATUS_ROWS (0)
#define POWER_ATTRIBUTE_PPU_FREQUENCY_ROWS (0)
#define POWER_ATTRIBUTE_PPU_DUTY_CYCLE_ROWS (0)
#define POWER_ATTRIBUTE_BUCKBOOST_STATUS_ROWS (0)
#define POWER_ATTRIBUTE_CURRENT_LIMIT_ROWS (0)


#define POWER_ATTRIBUTE_PPU_STATUS_ID (0)
#define POWER_ATTRIBUTE_PPU_FREQUENCY_ID (1)
#define POWER_ATTRIBUTE_PPU_DUTY_CYCLE_ID (2)
#define POWER_ATTRIBUTE_BUCKBOOST_STATUS_ID (3)
#define POWER_ATTRIBUTE_CURRENT_LIMIT_ID (4)


typedef struct _power_attributes {
    bool ppu_status; /* Is the PPU currently enabled? */
    uint16_t ppu_frequency; /* Frequency of PWM controlled Buck Boost (Hz) */
    uint8_t ppu_duty_cycle; /* Duty cycle of PWM controlled Buck Boost (%) */
    bool buckboost_status; /* Is the Buck-Boost currently enabled? */
    uint8_t current_limit; /* Sets the inrush settings which is used to control the firing power */
} power_attributes;



#endif