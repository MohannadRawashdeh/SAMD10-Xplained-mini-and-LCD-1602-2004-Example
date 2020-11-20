/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD10 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define LCD_EN GPIO(GPIO_PORTA, 9)
#define Data_pin_7 GPIO(GPIO_PORTA, 16)
#define Data_pin_6 GPIO(GPIO_PORTA, 17)
#define LCD_WR GPIO(GPIO_PORTA, 22)
#define Data_pin_4 GPIO(GPIO_PORTA, 23)
#define LCD_RS GPIO(GPIO_PORTA, 24)
#define Data_pin_5 GPIO(GPIO_PORTA, 27)

#endif // ATMEL_START_PINS_H_INCLUDED
