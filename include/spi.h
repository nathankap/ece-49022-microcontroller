#ifndef SPI_H
#define SPI_H

#include <stm32f0xx.h>

void spi_init(void);
void spi_data(unsigned int data);
void spi_cmd(unsigned int data);
void display_init(void);
void spi1_display1(const char *string);
void spi1_display2(const char *string);


#endif // SPI_H