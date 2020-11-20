/*
 * Liquid_Crystal.h
 *
 * Created: 3/30/2020 7:08:41 PM
 *  Author: Mohannad Rawashdeh
 * LCD Display driver for HD44780 driver or equivalent
 tested on LCD 1602 / 2004 / 2002 displays
 this library has been written based on https://github.com/arduino-libraries/LiquidCrystal library
 visit my website for more information
					 https://mb-raw.blogspot.com/
 */ 
#include "atmel_start.h"
struct LCD_param
{
	uint8_t LCD_RS_pin;
	uint8_t LCD_WR_pin;
	uint8_t LCD_EN_pin;
	uint8_t LCD_Data_pin[8];/*pin for LCD data 8/4 bit*/
	uint8_t LCD_Data_bit_Mode; /*LCD_8BITMODE or LCD_4BITMODE*/
	uint8_t LCD_Column;
	uint8_t LCD_Row;
	uint8_t LCD_function;
	uint8_t LCD_ctrl;
	uint8_t LCD_mode;
};

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

#ifndef LIQUID_CRYSTAL_H_
#define LIQUID_CRYSTAL_H_

void Liquid_Crystal_setup(struct LCD_param *lcd,uint8_t lcd_dataBitMode,
						   uint8_t RS_pin,uint8_t WR_pin,uint8_t EN_pin,
						   uint8_t D0,uint8_t D1,uint8_t D2,uint8_t D3,
						   uint8_t D4,uint8_t D5,uint8_t D6,uint8_t D7);

void Liquid_Crystal_initi(struct LCD_param *lcd,uint8_t lcd_col,uint8_t lcd_row);

void Liquid_Crystal_writeChar(struct LCD_param *lcd,uint8_t c);
void Liquid_Crystal_writeString(struct LCD_param *lcd,char str[]);

void Liquid_Crystal_display(struct LCD_param *lcd);

void Liquid_Crystal_noDisplay(struct LCD_param *lcd);

void Liquid_Crystal_clear(struct LCD_param *lcd);

void Liquid_Crystal_Home(struct LCD_param *lcd);
void Liquid_Crystal_setCursor(struct LCD_param *lcd,uint8_t col, uint8_t row);
void Liquid_Crystal_noBlink(struct LCD_param *lcd);
void Liquid_Crystal_blink(struct LCD_param *lcd);
void Liquid_Crystal_noCursor(struct LCD_param *lcd);
void Liquid_Crystal_cursor(struct LCD_param *lcd);
void Liquid_Crystal_scrollDisplayLeft(struct LCD_param *lcd);
void Liquid_Crystal_scrollDisplayRight(struct LCD_param *lcd);
void Liquid_Crystal_leftToRight(struct LCD_param *lcd);
void Liquid_Crystal_rightToLeft(struct LCD_param *lcd);
void Liquid_Crystal_autoscroll(struct LCD_param *lcd);
void Liquid_Crystal_noAutoscroll(struct LCD_param *lcd);
uint16_t Liquid_Crystal_version(void);
//void
#endif /* LIQUID_CRYSTAL_H_ */