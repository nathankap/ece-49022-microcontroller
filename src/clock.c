#include "clock.h"

void internal_clock(void) {
    // Enable the HSI (High-Speed Internal) oscillator (8 MHz)
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));  // Wait for HSI to stabilize

    // Set HSI as the system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;  // Clear clock source bits
    RCC->CFGR |= RCC_CFGR_SW_HSI;  // Set HSI as the system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);  // Wait for HSI to be selected
}