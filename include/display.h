#ifndef DISPLAY_H
#define DISPLAY_H

#include <stm32f0xx.h>

void display_init(void);
void display_write_char(char c);
void display_write_string(const char *str);
void display_set_cursor(uint8_t row, uint8_t col);

#endif // DISPLAY_H