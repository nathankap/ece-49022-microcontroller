#ifndef BUTTONS_H
#define BUTTONS_H

#include <stm32f0xx.h>

void check_buttons(void);
uint8_t is_button_pressed(uint32_t pin);
uint32_t get_tick(void);

#endif // BUTTONS_H