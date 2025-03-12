#include "stm32f0xx.h"
#include "motors.h"
#include <stdio.h>

void internal_clock();
void gpio_init();
void exti_init();



// In main(), replace the motor control section with this:
int main(void) 
{
    internal_clock();   // 48 MHz setup
    gpio_init();        // Basic GPIO for LED(s), etc.
    exti_init();        // If you want external interrupts
    init_motors();      // Initializes TIM3 PWM on PA6, PA7

    // Motor directions
    motor_direction_t motor1_dir = MOTOR_STOP;
    motor_direction_t motor2_dir = MOTOR_STOP;
    
    int motor_limit = 500;
    int limitx = 0;
    int limity = 0;
    // Initialize motors to stopped
    set_motor1_direction(motor1_dir);
    set_motor2_direction(motor2_dir);

    return 0;
}

// -------------------- Existing gpio_init & exti_init -------------------- //
void gpio_init() {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Already enabled but safe
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // Configure PA8, PA9, PA10 as outputs (debug LED, etc.)
    GPIOA->MODER &= ~(GPIO_MODER_MODER8_Msk | GPIO_MODER_MODER9_Msk | GPIO_MODER_MODER10_Msk);
    GPIOA->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0);

    // Configure Inputs PB0-B5 with pull-down (example usage)
    GPIOB->MODER &= ~(GPIO_MODER_MODER0_Msk | GPIO_MODER_MODER1_Msk |
                      GPIO_MODER_MODER2_Msk | GPIO_MODER_MODER3_Msk |
                      GPIO_MODER_MODER4_Msk | GPIO_MODER_MODER5_Msk);
    GPIOB->PUPDR &= ~0xFFF;
    GPIOB->PUPDR |= 0xAAA;

    // Configure PB7 as output (debug LED)
    GPIOB->MODER &= ~(GPIO_MODER_MODER7_Msk);
    GPIOB->MODER |= GPIO_MODER_MODER7_0;
}

void exti_init() {
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;

    // Example interrupt config for PA0-PA5
    SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI0_PA | SYSCFG_EXTICR1_EXTI1_PA | 
                          SYSCFG_EXTICR1_EXTI2_PA | SYSCFG_EXTICR1_EXTI3_PA);
    SYSCFG->EXTICR[1] |= (SYSCFG_EXTICR2_EXTI4_PA | SYSCFG_EXTICR2_EXTI5_PA);

    EXTI->FTSR |= (EXTI_FTSR_TR0 | EXTI_FTSR_TR1 | EXTI_FTSR_TR2 | 
                   EXTI_FTSR_TR3 | EXTI_FTSR_TR4 | EXTI_FTSR_TR5);
    EXTI->RTSR |= (EXTI_RTSR_TR0 | EXTI_RTSR_TR1 | EXTI_RTSR_TR2 |
                   EXTI_RTSR_TR3 | EXTI_RTSR_TR4 | EXTI_RTSR_TR5);

    EXTI->IMR |= (EXTI_IMR_IM0 | EXTI_IMR_IM1 | EXTI_IMR_IM2 |
                  EXTI_IMR_IM3 | EXTI_IMR_IM4 | EXTI_IMR_IM5);

    NVIC->ISER[0] |= ((1 << EXTI0_1_IRQn) | (1 << EXTI2_3_IRQn) | 
                      (1 << EXTI4_15_IRQn));
}