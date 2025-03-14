#include <stm32f0xx.h>
#include "spi.h"
#include "clock.h"
#include "gpio.h"
#include "delay.h"
#include "buttons.h"
#include "motors.h"


int main(void) {
    // Initialize system clock and GPIO
    internal_clock();
    gpio_init();
    spi_init();
    display_init();
    init_motors();

    while (1) {
        check_buttons();
    }
}

// init_adc();         // ADC for joystick on PA2, PA3

    // // Add this before your main loop to calibrate
    // uint16_t x_samples[10];
    // uint16_t y_samples[10];
    // uint16_t JOY_CENTER_X = 0;
    // uint16_t JOY_CENTER_Y = 0;

    // // Take 10 samples at startup with joystick centered
    // for (int i = 0; i < 10; i++) {
    //     x_samples[i] = read_adc_channel(2);
    //     y_samples[i] = read_adc_channel(3);
    //     // GPIOA->ODR ^= GPIO_ODR_8;
    //     for(volatile uint32_t delay = 0; delay < 10000; delay++); // Short delay

    // }

    // // Average the samples
    // for (int i = 0; i < 10; i++) {
    //     JOY_CENTER_X += x_samples[i];
    //     JOY_CENTER_Y += y_samples[i];
    // }
    // JOY_CENTER_X /= 10;
    // JOY_CENTER_Y /= 10;

    // // Use a slightly larger deadzone
    // const uint16_t JOY_DEADZONE = 700;

// Typical raw ADC range is 0..4095 for 12-bit
    // while(1) 
    // {
    //     // 1. Read the joystick channels
    //     uint16_t xVal = read_adc_channel(2); // VRx on PA2
    //     uint16_t yVal = read_adc_channel(3); // VRy on PA3

    //     // 2. Check X direction (right/left) for motor1
    //     if ((xVal > (JOY_CENTER_X + JOY_DEADZONE)) && limitx < motor_limit) {
    //         // Right - clockwise
    //         motor1_dir = MOTOR_CW;
    //         limitx += 5;
    //         // GPIOA->ODR = GPIO_ODR_8;
    //     }
    //     else if ((xVal < (JOY_CENTER_X - JOY_DEADZONE)) && limitx > -motor_limit) {
    //         // Left - counterclockwise
    //         motor1_dir = MOTOR_CCW;
    //         limitx -=5;
    //         // GPIOA->ODR = ~GPIO_ODR_8;
    //     }
    //     else {
    //         // Within deadzone - stop motor
    //         motor1_dir = MOTOR_STOP;
    //         // GPIOA->ODR = GPIO_ODR_8;
    //     }

    //     // 3. Check Y direction (up/down) for motor2
    //     if ((yVal > (JOY_CENTER_Y + JOY_DEADZONE)) && limity < motor_limit) {
    //         // Up - clockwise
    //         motor2_dir = MOTOR_CW;
    //         limity += 5;
    //         // GPIOA->ODR = GPIO_ODR_8;
    //     }
    //     else if ((yVal < (JOY_CENTER_Y - JOY_DEADZONE)) && limity > -motor_limit) {
    //         // Down - counterclockwise
    //         motor2_dir = MOTOR_CCW;
    //         limity -= 5;
    //         // GPIOA->ODR ^= GPIO_ODR_8;
    //         // GPIOA->ODR = ~GPIO_ODR_8;
    //     }
    //     else {
    //         // Within deadzone - stop motor
    //         motor2_dir = MOTOR_STOP;
    //         // GPIOA->ODR = GPIO_ODR_8;
    //     }

    //     // 4. Update motor directions
    //     set_motor1_direction(motor1_dir);
    //     set_motor2_direction(motor2_dir);

    //     // 5. Set PA8 equal to the
    //     // 6. Small delay so the system doesn't react too quickly
    //     for(volatile uint32_t delay = 0; delay < 20000; delay++);
    // }

