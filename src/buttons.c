#include "buttons.h"
#include "gpio.h"
#include "delay.h"
#include "spi.h"
#include <string.h>

// Global variables
uint8_t current_color_mode = 0;  // 0 = Tank 1, 1 = Tank 2, 2 = Tank 3, 3 = Cleaning
uint8_t current_system_mode = 0;  // 0 = Mode 1, 1 = Mode 2, 2 = Mode 3
uint8_t most_recent_system_mode = 0;  // Store the most recent system mode before cleaning
uint32_t last_toggle_time = 0;    // Track the last time the movement LEDs were toggled
char original_display1[17] = "Mode: 1         "; // Message before motion detection
char original_display2[17] = "Color Tank: 1   "; // Message before motion detection

// Main function
void check_buttons(void) {
    check_system_mode();
    check_color_mode();
    handle_motion_detection();
    handle_shooting();
    handle_movements();
}

// Check and update the system mode
void check_system_mode(void) {
    static uint8_t prev_mode_button_state = 1;  // Track previous state of PB11

    if (is_button_pressed(GPIO_IDR_11)) {
        if (prev_mode_button_state == 0) {  // Detect rising edge (button pressed)
            // Only allow mode change if not in cleaning mode
            if (current_color_mode != 3) {
                current_system_mode = (current_system_mode + 1) % 3;  // Cycle through system modes (0-2)
                switch(current_system_mode){
                    case (0): // Mode 1
                        spi1_display1("Mode: 1         ");
                        strcpy(original_display1, "Mode: 1         ");  // Update original message
                        break;
                    case (1): // Mode 2
                        spi1_display1("Mode: 2         ");
                        strcpy(original_display1, "Mode: 2         ");  // Update original message
                        break;
                    case (2): // Mode 3
                        spi1_display1("Mode: 3         ");
                        strcpy(original_display1, "Mode: 3         ");  // Update original message
                        break;
                }
            }
        }
        prev_mode_button_state = 1;  // Update previous state
    } else {
        prev_mode_button_state = 0;  // Update previous state
    }
}

// Check and update the color mode
void check_color_mode(void) {
    static uint8_t prev_color_button_state = 1;  // Track previous state of PB5

    if (is_button_pressed(GPIO_IDR_5)) {
        if (prev_color_button_state == 0) {  // Detect rising edge (button pressed)
            // Turn off the currently active tank
            GPIOB->ODR &= ~(GPIO_ODR_8 | GPIO_ODR_9 | GPIO_ODR_10);

            // Store the current system mode before entering cleaning mode
            if (current_color_mode != 3) {
                most_recent_system_mode = current_system_mode;
            }

            // Cycle through color modes (0-3)
            current_color_mode = (current_color_mode + 1) % 4;

            // Restore the most recent system mode when exiting cleaning mode
            if (current_color_mode != 3) {
                current_system_mode = most_recent_system_mode;
            } else {
                // Disable movements in cleaning mode
                GPIOB->ODR &= ~(GPIO_ODR_6 | GPIO_ODR_7);
            }

            switch(current_color_mode){
                case (0): // Tank 1
                    spi1_display2("Color Tank: 1   ");
                    strcpy(original_display2, "Color Tank: 1   ");  // Update original message
                    break;
                case (1): // Tank 2
                    spi1_display2("Color Tank: 2   ");
                    strcpy(original_display2, "Color Tank: 2   ");  // Update original message
                    break;
                case (2): // Tank 3
                    spi1_display2("Color Tank: 3   ");
                    strcpy(original_display2, "Color Tank: 3   ");  // Update original message
                    break;
                case (3): // Tank All
                    spi1_display2("Color Tank: All ");
                    strcpy(original_display2, "Color Tank: All ");  // Update original message
                    break;
            }

            // If shooting, immediately turn on the new tank
            if (is_button_pressed(GPIO_IDR_4)) {
                switch (current_color_mode) {
                    case 0:  // Tank 1 (PB8)
                        GPIOB->ODR |= GPIO_ODR_8;
                        break;
                    case 1:  // Tank 2 (PB9)
                        GPIOB->ODR |= GPIO_ODR_9;
                        break;
                    case 2:  // Tank 3 (PB10)
                        GPIOB->ODR |= GPIO_ODR_10;
                        break;
                    case 3:  // Cleaning (PB8, PB9, PB10)
                        GPIOB->ODR |= (GPIO_ODR_8 | GPIO_ODR_9 | GPIO_ODR_10);
                        break;
                }
            }
        }
        prev_color_button_state = 1;  // Update previous state
    } else {
        prev_color_button_state = 0;  // Update previous state
    }
}

// Handle motion detection logic
void handle_motion_detection(void) {
    // PB14 (PIR Motion Detector) controls PA0 (Laser)
    if (is_button_pressed(GPIO_IDR_14)) {
        GPIOA->ODR &= ~GPIO_ODR_0;  // Turn off PA0 (Laser) when motion is detected

        // Disable shooting when motion is detected
        GPIOB->ODR &= ~(GPIO_ODR_8 | GPIO_ODR_9 | GPIO_ODR_10);  // Turn off all tanks

        // Display motion detection messages
        spi1_display1("Motion detected!");
        spi1_display2("Paint disabled.");
    } else {
        GPIOA->ODR |= GPIO_ODR_0;  // Turn on PA0 (Laser) when no motion is detected

        // Restore the original messages
        spi1_display1(original_display1);
        spi1_display2(original_display2);
    }
}

// Handle shooting logic based on the current color mode
void handle_shooting(void) {
    if (!is_button_pressed(GPIO_IDR_14)) {  // Only enable shooting if no motion is detected
        if (is_button_pressed(GPIO_IDR_4)) {
            switch (current_color_mode) {
                case 0:  // Tank 1 (PB8)
                    GPIOB->ODR |= GPIO_ODR_8;
                    break;
                case 1:  // Tank 2 (PB9)
                    GPIOB->ODR |= GPIO_ODR_9;
                    break;
                case 2:  // Tank 3 (PB10)
                    GPIOB->ODR |= GPIO_ODR_10;
                    break;
                case 3:  // Cleaning (PB8, PB9, PB10)
                    GPIOB->ODR |= (GPIO_ODR_8 | GPIO_ODR_9 | GPIO_ODR_10);
                    break;
            }
        } else {
            // Turn off all tanks when the shoot button is released
            GPIOB->ODR &= ~(GPIO_ODR_8 | GPIO_ODR_9 | GPIO_ODR_10);
        }
    }
}

// Handle movement logic based on the current system mode
void handle_movements(void) {
    if (current_color_mode == 3) return;  // Disable movements in cleaning mode

    switch (current_system_mode) {
        case 0:  // Mode 1: Random horizontal and vertical movements while shooting
            if (is_button_pressed(GPIO_IDR_4)) {  // Only toggle while shooting
                if (get_tick() - last_toggle_time > 200) {  // Toggle every 200ms
                    GPIOB->ODR ^= (GPIO_ODR_6 | GPIO_ODR_7);  // Toggle PB6 and PB7
                    last_toggle_time = get_tick();
                }
            } else {
                GPIOB->ODR &= ~(GPIO_ODR_6 | GPIO_ODR_7);  // Turn off PB6 and PB7 when not shooting
            }
            break;

        case 1:  // Mode 2: Random vertical movements while shooting
            if (is_button_pressed(GPIO_IDR_4)) {  // Only toggle while shooting
                if (get_tick() - last_toggle_time > 200) {  // Toggle every 200ms
                    GPIOB->ODR ^= GPIO_ODR_7;  // Toggle PB7
                    last_toggle_time = get_tick();
                }
            } else {
                GPIOB->ODR &= ~GPIO_ODR_7;  // Turn off PB7 when not shooting
            }

            // Normal horizontal movements (independent of shooting)
            if (is_button_pressed(GPIO_IDR_0)) {
                GPIOB->ODR |= GPIO_ODR_6;  // Turn on PB6 (left)
            } else if (is_button_pressed(GPIO_IDR_1)) {
                GPIOB->ODR |= GPIO_ODR_6;  // Turn on PB6 (right)
            } else {
                GPIOB->ODR &= ~GPIO_ODR_6;  // Turn off PB6
            }
            break;

        case 2:  // Mode 3: All buttons behave normally
            // Horizontal movements (PB6)
            if (is_button_pressed(GPIO_IDR_0)) {
                GPIOB->ODR |= GPIO_ODR_6;  // Turn on PB6 (left)
            } else if (is_button_pressed(GPIO_IDR_1)) {
                GPIOB->ODR |= GPIO_ODR_6;  // Turn on PB6 (right)
            } else {
                GPIOB->ODR &= ~GPIO_ODR_6;  // Turn off PB6
            }

            // Vertical movements (PB7)
            if (is_button_pressed(GPIO_IDR_2)) {
                GPIOB->ODR |= GPIO_ODR_7;  // Turn on PB7 (up)
            } else if (is_button_pressed(GPIO_IDR_3)) {
                GPIOB->ODR |= GPIO_ODR_7;  // Turn on PB7 (down)
            } else {
                GPIOB->ODR &= ~GPIO_ODR_7;  // Turn off PB7
            }
            break;
    }
}

// Helper function to check if a button is pressed
uint8_t is_button_pressed(uint32_t pin) {
    if ((GPIOB->IDR & pin) == 0) {  // Button pressed (active low)
        delay(10000);  // Wait 10ms for debouncing
        if ((GPIOB->IDR & pin) == 0) {  // Confirm button is still pressed
            return 1;  // Button is pressed
        }
    }
    return 0;  // Button is not pressed
}

// Helper function to get the current tick (replace with a proper timer if available)
uint32_t get_tick(void) {
    static uint32_t tick = 0;
    return tick++;
}