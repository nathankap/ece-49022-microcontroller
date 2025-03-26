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
        // set_motor1_direction(MOTOR_CW);
        // set_motor2_direction(MOTOR_CW);
    }
}