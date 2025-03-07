#include "spi.h"

void spi_init(void) {
    // Enable GPIOB clock
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // Configure PB13 (SCK), PB15 (MOSI), and PB12 (NCS) as alternate function (AF0 for SPI2)
    GPIOB->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER15 | GPIO_MODER_MODER12);  // Clear mode bits
    GPIOB->MODER |= (GPIO_MODER_MODER13_1 | GPIO_MODER_MODER15_1 | GPIO_MODER_MODER12_1);  // Set to alternate function
    GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL13 | GPIO_AFRH_AFSEL15 | GPIO_AFRH_AFSEL12);  // Clear alternate function bits
    GPIOB->AFR[1] |= (0 << GPIO_AFRH_AFSEL13_Pos) | (0 << GPIO_AFRH_AFSEL15_Pos) | (0 << GPIO_AFRH_AFSEL12_Pos);  // Set to AF0

    // Enable SPI2 clock
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

    // Configure SPI2
    SPI2->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_BR_0;  // Master mode, baud rate = PCLK/16
    SPI2->CR2 = SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;  // 8-bit data frame
    SPI2->CR1 |= SPI_CR1_SPE;  // Enable SPI2
}

void spi_send_command(uint8_t command) {
    // Wait for the transmit buffer to be empty
    while ((SPI2->SR & SPI_SR_TXE) == 0);

    // Send the command (register select = 0)
    SPI2->DR = command;
}

void spi_send_data(uint8_t data) {
    // Wait for the transmit buffer to be empty
    while ((SPI2->SR & SPI_SR_TXE) == 0);

    // Send the data (register select = 1)
    SPI2->DR = 0x200 | data;  // 0x200 sets the register select bit
}

void spi_cs_low(void) {
    GPIOB->ODR &= ~GPIO_ODR_12;  // Set PB12 (NCS) low
}

void spi_cs_high(void) {
    GPIOB->ODR |= GPIO_ODR_12;  // Set PB12 (NCS) high
}