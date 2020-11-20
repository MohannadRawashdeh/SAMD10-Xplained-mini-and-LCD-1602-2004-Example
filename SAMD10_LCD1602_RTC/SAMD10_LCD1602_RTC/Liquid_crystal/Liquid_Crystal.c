/*
 * Liquid_Crystal.c
 *
 * Created: 3/30/2020 7:08:41 PM
 *  Author: Mohannad Rawashdeh
 * LCD Display driver for HD44780 driver or equivalent 
 tested on LCD 1602 / 2004 / 2002 displays
  this library has been written based on https://github.com/arduino-libraries/LiquidCrystal library
  visit my website for more information
  https://mb-raw.blogspot.com/ 
 */ 

#include "Liquid_crystal/Liquid_Crystal.h"
#include "atmel_start.h"
#include <string.h>
#define LOW   false
#define HIGH  true
/* static functions to use only here*/
static uint8_t row_offsets[4];
static void setRowOffsets(int row0, int row1, int row2, int row3)
{
	row_offsets[0]=row0;
	row_offsets[1]=row1;
	row_offsets[2]=row2;
	row_offsets[3]=row3;
}
static void lcd_delay_ms(uint16_t time_delay)
{
	delay_ms(time_delay);
}
static void lcd_delay_us(uint16_t time_delay)
{
	delay_us(time_delay);
}
static void lcd_set_output_level(uint8_t pin,uint8_t level)
{
	gpio_set_pin_level(pin,level);
}

static void pulseEnable(struct LCD_param *lcd) {
	lcd_set_output_level(lcd->LCD_EN_pin, LOW);
	lcd_delay_us(5);
	lcd_set_output_level(lcd->LCD_EN_pin, HIGH);
	lcd_delay_us(2);    // enable pulse must be >450ns
	lcd_set_output_level(lcd->LCD_EN_pin, LOW);
	lcd_delay_us(100);   // commands need > 37us to settle
}

static void write4bits(struct LCD_param *lcd,uint8_t value) {

	for (int i = 0; i <4; i++) 
	{
		lcd_set_output_level(lcd->LCD_Data_pin[i], (value >> i) & 0x01);
	}
	
	pulseEnable(lcd);
}
static void write8bits(struct LCD_param *lcd,uint8_t value) {
	for (int i = 0; i < 8; i++) {
		lcd_set_output_level(lcd->LCD_Data_pin[i], (value >> i) & 0x01);
	}
	pulseEnable(lcd);
}
static void send(struct LCD_param *lcd,uint8_t value, uint8_t mode) {
	lcd_set_output_level(lcd->LCD_RS_pin, mode);
	// if there is a RW pin indicated, set it low to Write
	lcd_set_output_level(lcd->LCD_WR_pin,LOW);
	
	if (lcd->LCD_function & LCD_8BITMODE) 
	    {
		write8bits(lcd,value);
		} else {
		write4bits(lcd,value>>4);
		write4bits(lcd,value);
		//write4bits(lcd,value<<4);
		
		
	}
}
void command(struct LCD_param *lcd,uint8_t value) 
{
	send(lcd,value, LOW);
}
/* end of static functions*/

void Liquid_Crystal_setup(struct LCD_param *lcd,uint8_t lcd_dataBitMode,
							uint8_t RS_pin,uint8_t WR_pin,uint8_t EN_pin,
							uint8_t D0,uint8_t D1,uint8_t D2,uint8_t D3,
							uint8_t D4,uint8_t D5,uint8_t D6,uint8_t D7)
{
	lcd->LCD_RS_pin=RS_pin;
	lcd->LCD_WR_pin=WR_pin;
	lcd->LCD_EN_pin=EN_pin;
	lcd->LCD_Data_bit_Mode=lcd_dataBitMode;
	lcd->LCD_Data_pin[0]=D0;
	lcd->LCD_Data_pin[1]=D1;
	lcd->LCD_Data_pin[2]=D2;
	lcd->LCD_Data_pin[3]=D3;
	lcd->LCD_Data_pin[4]=D4;
	lcd->LCD_Data_pin[5]=D5;
	lcd->LCD_Data_pin[6]=D6;
	lcd->LCD_Data_pin[7]=D7;
	if (lcd->LCD_Data_bit_Mode == LCD_4BITMODE)
	{
		lcd->LCD_function = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	}
	else if (lcd->LCD_Data_bit_Mode == LCD_8BITMODE)
	{
		lcd->LCD_function = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
	}
	
	Liquid_Crystal_initi(lcd,16,1);
}

void Liquid_Crystal_initi(struct LCD_param *lcd,uint8_t lcd_col,uint8_t lcd_row)
{
	lcd->LCD_Column=lcd_col;
	lcd->LCD_Row   =lcd_row;
	setRowOffsets(0x00, 0x40, 0x00 + lcd_col, 0x40 + lcd_col);
	if (lcd->LCD_Row>1)
	{
		lcd->LCD_function |= LCD_2LINE;
	}
	lcd_delay_ms(50);
	lcd_set_output_level(lcd->LCD_RS_pin,LOW);
	lcd_set_output_level(lcd->LCD_EN_pin,LOW);
	/*if you use R/W pin*/
	lcd_set_output_level(lcd->LCD_WR_pin,LOW);
	lcd_delay_ms(50);
	if (! (lcd->LCD_function & LCD_8BITMODE)) {
		// this is according to the hitachi HD44780 datasheet
		// figure 24, pg 46
		// we start in 8bit mode, try to set 4 bit mode
		write4bits(lcd,0x03);
		lcd_delay_ms(5); // wait min 4.1ms
		write4bits(lcd,0x03);
		lcd_delay_ms(5); // wait min 4.1ms
		write4bits(lcd,0x03);
		lcd_delay_us(200);
		write4bits(lcd,0x02);
		} 
		else 
		{
		// this is according to the hitachi HD44780 datasheet
		// page 45 figure 23
		command(lcd ,(LCD_FUNCTIONSET | lcd->LCD_function));
		lcd_delay_ms(5);  // wait more than 4.1ms
		command(lcd ,(LCD_FUNCTIONSET | lcd->LCD_function));
		lcd_delay_us(150);
		command(lcd ,(LCD_FUNCTIONSET | lcd->LCD_function));
	}

	// finally, set # lines, font size, etc.
	command(lcd ,(LCD_FUNCTIONSET | lcd->LCD_function));

	// turn the display on with  cursor and blinking on
	lcd->LCD_ctrl = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON;
	Liquid_Crystal_display(lcd);

	// clear it off
	Liquid_Crystal_clear(lcd);

	// Initialize to default text direction (for romance languages)
	lcd->LCD_mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	command(lcd ,LCD_ENTRYMODESET | lcd->LCD_mode);	
}

void Liquid_Crystal_writeChar(struct LCD_param *lcd,uint8_t c)
{
	send(lcd,c, HIGH);
}

void Liquid_Crystal_writeString(struct LCD_param *lcd,char str[])
{
	uint8_t str_size=strlen(str);
	for (uint8_t i=0;i<str_size;i++)
	{
		Liquid_Crystal_writeChar(lcd,str[i]);
	}
}

void Liquid_Crystal_display(struct LCD_param *lcd) {
	lcd->LCD_ctrl |= LCD_DISPLAYON;
	command(lcd,LCD_DISPLAYCONTROL | lcd->LCD_ctrl);
}

void Liquid_Crystal_noDisplay(struct LCD_param *lcd) {
	lcd->LCD_ctrl &= ~LCD_DISPLAYON;
	command(lcd,LCD_DISPLAYCONTROL | lcd->LCD_ctrl);
}

void Liquid_Crystal_clear(struct LCD_param *lcd)
{
	command(lcd,LCD_CLEARDISPLAY);
	lcd_delay_ms(10); 
	Liquid_Crystal_Home(lcd);
}

void Liquid_Crystal_Home(struct LCD_param *lcd)
{
	command(lcd,LCD_RETURNHOME);  // set cursor position to zero
	lcd_delay_ms(10);
}

void Liquid_Crystal_setCursor(struct LCD_param *lcd,uint8_t col, uint8_t row)
{
	const size_t max_lines = sizeof(row_offsets) / sizeof(*row_offsets);
	if ( row >= max_lines ) {
		row = max_lines - 1;    // we count rows starting w/0
	}
	if ( row >= lcd->LCD_Row ) {
		row = lcd->LCD_Row - 1;    // we count rows starting w/0
	}
	
	command(lcd,LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void Liquid_Crystal_noBlink(struct LCD_param *lcd)
{
	 lcd->LCD_ctrl &= ~LCD_BLINKON;
	 command(lcd,LCD_DISPLAYCONTROL | lcd->LCD_ctrl);
}
void Liquid_Crystal_blink(struct LCD_param *lcd)
{
	lcd->LCD_ctrl |= LCD_BLINKON;
	command(lcd,LCD_DISPLAYCONTROL | lcd->LCD_ctrl);
}
void Liquid_Crystal_noCursor(struct LCD_param *lcd)
{
	lcd->LCD_ctrl &= ~LCD_CURSORON;
	command(lcd,LCD_DISPLAYCONTROL | lcd->LCD_ctrl);
}
void Liquid_Crystal_cursor(struct LCD_param *lcd)
{
	lcd->LCD_ctrl |= LCD_CURSORON;
	command(lcd,LCD_DISPLAYCONTROL | lcd->LCD_ctrl);
}
void Liquid_Crystal_scrollDisplayLeft(struct LCD_param *lcd)
{
	command(lcd,LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void Liquid_Crystal_scrollDisplayRight(struct LCD_param *lcd)
{
	 command(lcd,LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}
void Liquid_Crystal_leftToRight(struct LCD_param *lcd)
{
	 lcd->LCD_mode &= ~LCD_ENTRYLEFT;
	 command(lcd,LCD_ENTRYMODESET | lcd->LCD_mode);
}
void Liquid_Crystal_rightToLeft(struct LCD_param *lcd)
{
	lcd->LCD_mode |= LCD_ENTRYLEFT;
	command(lcd,LCD_ENTRYMODESET | lcd->LCD_mode);
}
void Liquid_Crystal_autoscroll(struct LCD_param *lcd)
{
	lcd->LCD_mode |= LCD_ENTRYSHIFTINCREMENT;
	command(lcd,LCD_ENTRYMODESET | lcd->LCD_mode);
}
void Liquid_Crystal_noAutoscroll(struct LCD_param *lcd)
{
	lcd->LCD_mode &= ~ LCD_ENTRYSHIFTINCREMENT;
	command(lcd,LCD_ENTRYMODESET | lcd->LCD_mode);
}
uint16_t Liquid_Crystal_version(void)
{
	return 100;/*version 1.0.0*/
}