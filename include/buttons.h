#ifndef BUTTONS_H
#define BUTTONS_H

#include <stm32f0xx.h>

void orientation(void);
void check_buttons(void);
void check_system_mode(void);
void check_color_mode(void);
void handle_motion_detection(void);
void handle_shooting(void);
void handle_movements(void);
uint8_t is_button_pressed(uint32_t pin);
uint32_t get_tick(void);

#define ANGLE_MIN -50    // Adjust based on your needs
#define ANGLE_MAX 50 // Adjust based on your needs
#define TOGGLE_AMT 3
int vertical_angle;   // Current vertical position (UP IS CW)
int horizontal_angle; // Current horizontal position (RIGHT IS CW)

#endif // BUTTONS_H