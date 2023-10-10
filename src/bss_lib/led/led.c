#include "led.h"
#include "asf.h"

void led0_on() {
    ioport_set_pin_level(LED0_GPIO, IOPORT_PIN_LEVEL_HIGH);
}

void led1_on() {
    ioport_set_pin_level(LED1_GPIO, IOPORT_PIN_LEVEL_HIGH);
}

void led0_off() {
    ioport_set_pin_level(LED0_GPIO, IOPORT_PIN_LEVEL_LOW);
}

void led1_off() {
    ioport_set_pin_level(LED1_GPIO, IOPORT_PIN_LEVEL_LOW);
}

void led0_toggle() {
    ioport_toggle_pin_level(LED0_GPIO);
}

void led1_toggle() {
    ioport_toggle_pin_level(LED1_GPIO);
}

void led_init() {
    ioport_set_pin_dir(LED0_GPIO, IOPORT_DIR_OUTPUT);
    ioport_set_pin_dir(LED1_GPIO, IOPORT_DIR_OUTPUT);
}