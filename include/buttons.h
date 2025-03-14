#ifndef BUTTONS_H
#define BUTTONS_H

#include <stm32f0xx.h>

void check_buttons(void);
void check_system_mode(void);
void check_color_mode(void);
void handle_motion_detection(void);
void handle_shooting(void);
void handle_movements(void);
uint8_t is_button_pressed(uint32_t pin);
uint32_t get_tick(void);

#endif // BUTTONS_H