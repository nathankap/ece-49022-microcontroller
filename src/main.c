#include "stm32f0xx.h"
#include "motors.h"
#include <stdio.h>

void internal_clock();
void gpio_init();
void exti_init();

// // -------------------- ADC Setup & Read -------------------- //
// static void init_adc(void)
// {
//     // 1. Enable clock to ADC and GPIOA
//     RCC->APB2ENR |= RCC_APB2ENR_ADCEN;   // ADC clock enable
//     RCC->AHBENR  |= RCC_AHBENR_GPIOAEN; // Already enabled in gpio_init, but safe here

//     // 2. Configure PA2 and PA3 as analog (0b11 in MODER)
//     GPIOA->MODER |= (3 << (2*2)) | (3 << (2*3)); // PA2, PA3 analog mode
//     // No pull-up/pull-down needed for analog
//     GPIOA->PUPDR &= ~((3 << (2*2)) | (3 << (2*3)));

//     // 3. Make sure ADC is disabled before configuring
//     if ((ADC1->CR & ADC_CR_ADEN) != 0) {
//         // If ADC is enabled, disable it and wait
//         ADC1->CR |= ADC_CR_ADDIS;
//         while ((ADC1->CR & ADC_CR_ADEN) != 0);
//     }

//     // 4. Calibrate ADC (optional but recommended for accuracy)
//     ADC1->CR |= ADC_CR_ADCAL;
//     while ((ADC1->CR & ADC_CR_ADCAL) != 0); // wait until calibration done

//     // 5. Enable the ADC
//     ADC1->CR |= ADC_CR_ADEN;
//     while ((ADC1->ISR & ADC_ISR_ADRDY) == 0); // wait until ADC is ready
// }

// // Simple blocking ADC read of a single channel
// static uint16_t read_adc_channel(uint8_t channel)
// {
//     // 1. Select channel
//     ADC1->CHSELR = (1 << channel); // e.g. channel 2 => bit 2
//     // 2. Start conversion
//     ADC1->CR |= ADC_CR_ADSTART;
//     // 3. Wait for end-of-conversion
//     while ((ADC1->ISR & ADC_ISR_EOC) == 0);
//     // 4. Read data (12-bit result)
//     return (uint16_t)(ADC1->DR & 0x0FFF);
// }
// ---------------------------------------------------------- //


// In main(), replace the motor control section with this:
int main(void) 
{
    internal_clock();   // 48 MHz setup
    gpio_init();        // Basic GPIO for LED(s), etc.
    exti_init();        // If you want external interrupts
    init_motors();      // Initializes TIM3 PWM on PA6, PA7
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

    // Motor directions
    motor_direction_t motor1_dir = MOTOR_STOP;
    motor_direction_t motor2_dir = MOTOR_STOP;
    
    int motor_limit = 500;
    int limitx = 0;
    int limity = 0;
    // Initialize motors to stopped
    set_motor1_direction(motor1_dir);
    set_motor2_direction(motor2_dir);

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