#include "stm32f0xx.h"
void internal_clock();
void gpio_init();
void exti_init();
main(void) {
    internal_clock();
    // Initializations
    gpio_init();
    exti_init();
}

void gpio_init() {
    // RCC Clock for GPIOA and GPIOB
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // GPIOA
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // GPIOB

    // Outputs (GPIOB6-B10)
    GPIOB->MODER &= ~(GPIO_MODER_MODER6_Msk | GPIO_MODER_MODER7_Msk | GPIO_MODER_MODER8_Msk | GPIO_MODER_MODER9_Msk | GPIO_MODER_MODER10_Msk);
    GPIOB->MODER |= (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0);

    // Inputs (GPIOA0-A5)
    //  *added pull down resistors for each input
    GPIOA->MODER &= ~(GPIO_MODER_MODER0_Msk | GPIO_MODER_MODER1_Msk | GPIO_MODER_MODER2_Msk | GPIO_MODER_MODER3_Msk | GPIO_MODER_MODER4_Msk | GPIO_MODER_MODER5_Msk);
    GPIOA->PUPDR &= ~0xfff;
    GPIOA->PUPDR |= 0xaaa;
}

void exti_init() {
    // RCC Clock
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;

    // Interrupt sources (A0-A5)
    SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI0_PA | SYSCFG_EXTICR1_EXTI1_PA | SYSCFG_EXTICR1_EXTI2_PA | SYSCFG_EXTICR1_EXTI3_PA); // PA0-A3
    SYSCFG->EXTICR[1] |= (SYSCFG_EXTICR2_EXTI4_PA | SYSCFG_EXTICR2_EXTI5_PA ); // PA4-A5

    // Falling edge (button press, A0-A5)
    EXTI->FTSR |= (EXTI_FTSR_TR0 | EXTI_FTSR_TR1 | EXTI_FTSR_TR2 | EXTI_FTSR_TR3 | EXTI_FTSR_TR4 | EXTI_FTSR_TR5);

    // Rising edge (button release, A0-A5)
    EXTI->RTSR |= (EXTI_RTSR_TR0 | EXTI_RTSR_TR1 | EXTI_RTSR_TR2 | EXTI_RTSR_TR3 | EXTI_RTSR_TR4 | EXTI_RTSR_TR5);

    // Unmasking (A0-A5)
    EXTI->IMR |= (EXTI_IMR_IM0 | EXTI_IMR_IM1 | EXTI_IMR_IM2 | EXTI_IMR_IM3 | EXTI_IMR_IM4 | EXTI_IMR_IM5);

    // Enable interrupts
    NVIC->ISER[0] |= ((1 << EXTI0_1_IRQn) | (1 << EXTI2_3_IRQn) | (1 << EXTI4_15_IRQn));

}