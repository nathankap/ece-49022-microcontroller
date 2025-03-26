#include "stm32f0xx.h"
#include "motors.h"

// PWM period for 50Hz (20ms) with 48MHz clock
#define PWM_PERIOD (48000000/50)
// Pulse width for 1.1ms center position - stop
#define STOP_PULSE1 (PWM_PERIOD * 1.1 / 20.0)
// Pulse width for 1.6ms - clockwise rotation
#define CW_PULSE1 (PWM_PERIOD * 1.59 / 20.0)
// Pulse width for 2.24ms - counterclockwise rotation
#define CCW_PULSE1 (PWM_PERIOD * 2.24 / 20.0)

#define STOP_PULSE2 (PWM_PERIOD * 1.1 / 20.0)

#define CW_PULSE2 (PWM_PERIOD * 1.59 / 20.0)

#define CCW_PULSE2 (PWM_PERIOD * 2.24 / 20.0)

void init_motors(void) {
    // Enable clock for GPIOC and TIM3
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Configure PC6 and PC7 as alternate function (TIM3 channels)
    GPIOC->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
    GPIOC->MODER |= (GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);

    // Set alternate function to AF0 (TIM3)
    GPIOC->AFR[0] &= ~(0xFF << (4 * 6)); // Clear existing AF settings for PC6 and PC7
    GPIOC->AFR[0] |= (0 << (4 * 6)) | (0 << (4 * 7)); // Set AF0 for PC6 and PC7
    
    // Configure timer
    TIM3->PSC = 0;                // No prescaler
    TIM3->ARR = PWM_PERIOD - 1;   // Auto-reload value

    // Configure channels 1 and 2 as PWM mode 1
    TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
    TIM3->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 |
                    TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
    TIM3->CCMR1 |= (TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE);


    // Enable outputs
    TIM3->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);

    // Update registers and start timer
    TIM3->EGR |= TIM_EGR_UG;
    TIM3->CR1 |= TIM_CR1_CEN;

    // Initialize servos to stopped position
    set_motor1_direction(MOTOR_STOP);
    set_motor2_direction(MOTOR_STOP);
}

// Set motor1 direction: MOTOR_CW, MOTOR_CCW, or MOTOR_STOP
void set_motor1_direction(motor_direction_t direction) {
    uint32_t pulse;
    
    switch(direction) {
        case MOTOR_CW:
            pulse = CW_PULSE1;
            break;
        case MOTOR_CCW:
            pulse = CCW_PULSE1;
            break;
        case MOTOR_STOP:
        default:
            pulse = STOP_PULSE1;
            break;
    }
    
    TIM3->CCR1 = pulse;
}

// Set motor2 direction: MOTOR_CW, MOTOR_CCW, or MOTOR_STOP
void set_motor2_direction(motor_direction_t direction) {
    uint32_t pulse;
    
    switch(direction) {
        case MOTOR_CW:
            pulse = CW_PULSE2;
            break;
        case MOTOR_CCW:
            pulse = CCW_PULSE2;
            break;
        case MOTOR_STOP:
        default:
            pulse = STOP_PULSE2;
            break;
    }
    
    TIM3->CCR2 = pulse;
}