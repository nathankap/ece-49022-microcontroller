#include "display.h"
#include "spi.h"
#include "delay.h"

#include "display.h"
#include "spi.h"

void display_init(void) {
    // Wait 1ms for display power to stabilize
    delay(1000);

    // Function Set: 8-bit mode, 2-line display, 5x8 font
    spi_cs_low();
    spi_send_command(0x38);
    spi_cs_high();
    delay(600);  // Wait 600µs

    // Display OFF
    spi_cs_low();
    spi_send_command(0x08);
    spi_cs_high();
    delay(600);  // Wait 600µs

    // Display Clear
    spi_cs_low();
    spi_send_command(0x01);
    spi_cs_high();
    delay(2000);  // Wait 2ms

    // Entry Mode Set: Increment cursor, no display shift
    spi_cs_low();
    spi_send_command(0x06);
    spi_cs_high();
    delay(600);  // Wait 600µs

    // Display ON
    spi_cs_low();
    spi_send_command(0x0C);
    spi_cs_high();
    delay(600);  // Wait 600µs

    // Write a test message
    display_set_cursor(0, 0);
    display_write_string("Hello, World!");
}

void display_write_char(char c) {
    spi_send_data(c);
}

void display_write_string(const char *str) {
    while (*str) {
        display_write_char(*str++);
    }
}

void display_set_cursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? 0x80 : 0xC0;  // Row 0: 0x80, Row 1: 0xC0
    address += col;  // Add column offset
    spi_send_command(address);
}