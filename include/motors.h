#ifndef MOTORS_H
#define MOTORS_H

#include <stdint.h>

// Define motor directions
typedef enum {
    MOTOR_STOP,
    MOTOR_CW,
    MOTOR_CCW
} motor_direction_t;

void init_motors(void);
void set_motor1_direction(motor_direction_t direction);
void set_motor2_direction(motor_direction_t direction);

#endif /* MOTORS_H */