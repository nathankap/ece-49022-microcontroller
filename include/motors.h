#ifndef MOTORS_H
#define MOTORS_H

#include "stm32f0xx.h"


// Initialize the motor GPIO pins and PWM
void init_motors(void);

// Control individual motors (angle from 0 to 180 degrees) 0 is counterclockwise and 180 is clockwise
void set_motor1_angle(uint8_t angle);
void set_motor2_angle(uint8_t angle);

#endif // MOTORS_H