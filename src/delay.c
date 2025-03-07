#include "delay.h"

void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");  // No operation (waste time)
    }
}

#include "gpio.h"
#include "delay.h"

uint8_t debounce_button(uint32_t pin) {
    if ((GPIOB->IDR & pin) == 0) {  // Button pressed (active low)
        delay(10000);  // Wait 10ms for debouncing
        if ((GPIOB->IDR & pin) == 0) {  // Confirm button is still pressed
            return 1;  // Button is pressed
        }
    }
    return 0;  // Button is not pressed
}

