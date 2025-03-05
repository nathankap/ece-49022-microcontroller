#include "stm32f0xx.h"
#include "motors.h"

// PWM period for 50Hz (20ms) with 48MHz clock
#define PWM_PERIOD 48000000/50000

void init_motors(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    
    GPIOB->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
    GPIOB->MODER |= (GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);
    
    GPIOB->AFR[0] &= ~(0xFF000000);
    GPIOB->AFR[0] |= (0x22000000);
    
    TIM3->PSC = 0;              // No prescaler
    TIM3->ARR = PWM_PERIOD - 1; // Auto-reload value for 50Hz
    
    TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
    TIM3->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 |
                    TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
    
    TIM3->CCMR1 |= (TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE);
    
    TIM3->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);
    
    TIM3->CR1 |= TIM_CR1_CEN;
    
    set_motor1_angle(90);
    set_motor2_angle(90);
}

void set_motor1_angle(uint8_t angle) {
    uint32_t pulse = (PWM_PERIOD/20) + 
                    (angle * (PWM_PERIOD/20))/180;
    TIM3->CCR1 = pulse;
}

void set_motor2_angle(uint8_t angle) {
    uint32_t pulse = (PWM_PERIOD/20) + 
                    (angle * (PWM_PERIOD/20))/180;
    TIM3->CCR2 = pulse;
}