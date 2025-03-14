#include <stm32f0xx.h>
#include "spi.h"
#include "clock.h"
#include "gpio.h"
#include "delay.h"
#include "buttons.h"


int main(void) {
    // Initialize system clock and GPIO
    internal_clock();
    gpio_init();
    spi_init();
    display_init();

    while (1) {
        check_buttons();
    }
}

