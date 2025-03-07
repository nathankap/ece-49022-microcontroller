#ifndef SPI_H
#define SPI_H

#include <stm32f0xx.h>

void spi_init(void);
void spi_send_command(uint8_t command);
void spi_send_data(uint8_t data);
void spi_cs_low(void);
void spi_cs_high(void);

#endif // SPI_H