#include "spi.h"
#include "delay.h"

void spi_init(void) {
    // Enable GPIOB clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= 0x3fff33ff;
    GPIOA->MODER |= 0x80008800;
    GPIOA->AFR[0] = 0x00000000;

    //Enable SPI clock
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    //Clear CR1_SPE bit
    SPI1->CR1 &= ~SPI_CR1_SPE;
    //Set baud rate & master mode (/256)
    SPI1->CR1 |=  SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;
    // Interface for 10-bit word size (1001)
    SPI1->CR2 = SPI_CR2_DS_3 | SPI_CR2_DS_0;
    //master configuration
    SPI1->CR1 |= SPI_CR1_MSTR;
    //SS output, NSSP
    SPI1->CR2 |= SPI_CR2_SSOE | SPI_CR2_NSSP ; 
    //TXDMAEN enable
    SPI1->CR2 |= SPI_CR2_TXDMAEN;
    //Enable SPI
    SPI1->CR1 |= SPI_CR1_SPE;
}

void spi_data(unsigned int data) {
    // calls spi_cmd with (data | 0x200)
    spi_cmd(data|0x200);
}

void spi_cmd(unsigned int data) {
    // wait until SPI1 TX is empty
    while(!(SPI1->SR & SPI_SR_TXE));
    // copy data to SPI1 data register
    SPI1->DR = data;
}

void display_init(void) {
    // wait 1 ms using nano_wait
    delay(1000);
    // call spi_cmd with 0x38 to do a "function set"
    spi_cmd(0x38);
    // call spi_cmd with 0x08 to turn the display off
    spi_cmd(0x08);
    // call spi_cmd with 0x01 to clear the display
    spi_cmd(0x01);
    // wait 2 ms using nano_wait
    delay(2000);
    // call spi_cmd with 0x06 to set the entry mode
    spi_cmd(0x06);
    // call spi_cmd with 0x02 to move the cursor to the home position
    spi_cmd(0x02);
    // call spi_cmd with 0x0c to turn the display on
    spi_cmd(0x0c);

    // // Start up message
    // spi1_display1("Purdue CREATE");
    // spi1_display2("Loading...");
    // // wait 5 seconds
    // delay(5000000);

    // Initialize msg
    spi1_display1("Mode: 1         ");
    spi1_display2("Color Tank: 1   ");
}

void spi1_display1(const char *string) {
    // move the cursor to the home position (this is the top row)
    spi_cmd(0x02);
    // for each character in the string
    while(*string){
        // call spi_data with the character
        spi_data(*string);
        string++;
    }
}
void spi1_display2(const char *string) {
    // move the cursor to the second row (0xc0)
    spi_cmd(0xc0);
    // for each character in the string
    while(*string){
        // call spi_data with the character
        spi_data(*string);
        string++;
    }
}