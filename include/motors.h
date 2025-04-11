#ifndef MOTORS_H
#define MOTORS_H

#include <stdint.h>

// Define motor directions
typedef enum {
    MOTOR_STOP,
    MOTOR_CW,
    MOTOR_CCW
} motor_direction_t;

// Motor angle tracking (in degrees * 10 for precision)
typedef struct {
    int16_t current_angle;   // Current position (e.g., 150 = 15.0°)
    int16_t min_angle;       // Minimum allowed angle (test to determine)
    int16_t max_angle;       // Maximum allowed angle (test to determine)
} motor_angle_t;

// PWM period for 50Hz (20ms) with 48MHz clock
#define PWM_PERIOD (48000000/50)
// Pulse width for 1.1ms center position - stop
#define STOP_PULSE1 (PWM_PERIOD * 1.1 / 20.0)
// Pulse width for 1.6ms - clockwise rotation
#define CW_PULSE1 (PWM_PERIOD * 1.59 / 20.0)
// Pulse width for 2.24ms - counterclockwise rotation
#define CCW_PULSE1 (PWM_PERIOD * 2.24 / 20.0)
#define STOP_PULSE2 (PWM_PERIOD * 1.1 / 20.0)
#define CW_PULSE2 (PWM_PERIOD * 1.59 / 20.0)
#define CCW_PULSE2 (PWM_PERIOD * 2.24 / 20.0)

// #define DEFAULT_ANGLE_RANGE 30  // ±15° range (adjust as needed)
// motor_angle_t vertical_motor = {0, -DEFAULT_ANGLE_RANGE, DEFAULT_ANGLE_RANGE};
// motor_angle_t horizontal_motor = {0, -DEFAULT_ANGLE_RANGE, DEFAULT_ANGLE_RANGE};

void init_motors(void);
void set_motor1_direction(motor_direction_t direction);
void set_motor2_direction(motor_direction_t direction);




#endif /* MOTORS_H */