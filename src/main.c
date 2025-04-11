#include <stm32f0xx.h>
#include "spi.h"
#include "clock.h"
#include "gpio.h"
#include "delay.h"
#include "buttons.h"
#include "motors.h"


int main(void) {
    internal_clock();
    gpio_init();
    spi_init();
    display_init();
    init_motors();
    orientation();
    while (1) {
        check_buttons();
    }
}