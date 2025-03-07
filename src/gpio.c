#include <stm32f0xx.h>

void gpio_init(void) {
    // Enable GPIOA and GPIOB clocks
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;

    // Configure PA0 as output (laser)
    GPIOA->MODER &= ~GPIO_MODER_MODER0;  // Clear mode bits for PA0
    GPIOA->MODER |= GPIO_MODER_MODER0_0;  // Set PA0 to output mode
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT_0;  // Set PA0 to push-pull
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR0;  // Set PA0 to low speed
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;  // No pull-up/pull-down for PA0

    // Configure PB6 and PB7 as outputs (motors)
    GPIOB->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);  // Clear mode bits for PB6 and PB7
    GPIOB->MODER |= (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0);  // Set PB6 and PB7 to output mode
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7);  // Set PB6 and PB7 to push-pull
    GPIOB->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR6 | GPIO_OSPEEDR_OSPEEDR7);  // Set PB6 and PB7 to low speed
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR6 | GPIO_PUPDR_PUPDR7);  // No pull-up/pull-down for PB6 and PB7
    
    // Initialize PB6 and PB7 to off
    GPIOB->ODR &= ~(GPIO_ODR_6 | GPIO_ODR_7);  // Turn off PB6 and PB7

    // Configure PB8, PB9, and PB10 as outputs (pumps)
    GPIOB->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9 | GPIO_MODER_MODER10);  // Clear mode bits for PB8, PB9, PB10
    GPIOB->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0);  // Set PB8, PB9, PB10 to output mode
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10);  // Set PB8, PB9, PB10 to push-pull
    GPIOB->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR8 | GPIO_OSPEEDR_OSPEEDR9 | GPIO_OSPEEDR_OSPEEDR10);  // Set PB8, PB9, PB10 to low speed
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9 | GPIO_PUPDR_PUPDR10);  // No pull-up/pull-down for PB8, PB9, PB10

    // Initialize PB8, PB9, and PB10 to off
    GPIOB->ODR &= ~(GPIO_ODR_8 | GPIO_ODR_9 | GPIO_ODR_10);  // Turn off PB8, PB9, and PB10

     // Configure PC0, PC1, and PC2 as outputs (mode selection)
     GPIOC->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2);
     GPIOC->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0);  
     GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_0 | GPIO_OTYPER_OT_1 | GPIO_OTYPER_OT_2);  
     GPIOC->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0 | GPIO_OSPEEDR_OSPEEDR1 | GPIO_OSPEEDR_OSPEEDR2);  
     GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2);  

    // Configure PB0-PB5 and PB11 as inputs with pull-up resistors (buttons)
    GPIOB->MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 |
                      GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 |
                      GPIO_MODER_MODER11);  // Clear mode bits for PB0-PB5 and PB11
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2 |
                      GPIO_PUPDR_PUPDR3 | GPIO_PUPDR_PUPDR4 | GPIO_PUPDR_PUPDR5 |
                      GPIO_PUPDR_PUPDR11);  // Clear pull-up/pull-down bits
    GPIOB->PUPDR |= (GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0 |
                     GPIO_PUPDR_PUPDR3_0 | GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0 |
                     GPIO_PUPDR_PUPDR11_0);  // Set PB0-PB5 and PB11 to pull-up

    // Configure PB14 as input with pull-up resistor (PIR motion detector)
    GPIOB->MODER &= ~GPIO_MODER_MODER14;  // Clear mode bits for PB14
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR14;  // Clear pull-up/pull-down bits
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR14_0;  // Set PB14 to pull-up
}