/*LCD 1602 with SAMD2=10 Xplaine mini example
written by: M.Rawashdeh
Please learn more about SAMD10 Xplained mini and how to program it please visit my course:
https://www.udemy.com/course/embedded-system-c-in-5-minutes-for-arm-cortex-atsamd10-xmini/?referralCode=CA9B9A9ACC9234F90A14
rawashdeh.mohannad@gmail.com
*/
#include <atmel_start.h>
/*			LCD Definition		*/
#include "Liquid_crystal/Liquid_Crystal.h"
#include "string.h"
#include <stdio.h>
struct LCD_param lcd1602;

/*			RTC Definition			*/
struct calendar_date set_rtc_date;
struct calendar_time set_rtc_time;
struct calendar_date_time rtc_date_time;
char Time_string[9];	//12:02:07
char Date_string[11];	//17/05/2020
/*			RTC Functions*/
void init_RTC_function();
void read_RTC_function();
void write_RTC_function();
void setup_lcd();
void init_RTC_function()
{
	calendar_enable(&CALENDAR_0);
}
void write_RTC_function()
{
	set_rtc_date.year	=2020;
	set_rtc_date.month	=11;
	set_rtc_date.day	=20;
	
	set_rtc_time.hour	=1;
	set_rtc_time.min	=25;
	set_rtc_time.sec	=0;
	
	calendar_set_date(&CALENDAR_0,&set_rtc_date);
	calendar_set_time(&CALENDAR_0,&set_rtc_time);
}
void read_RTC_function()
{
	calendar_get_date_time(&CALENDAR_0,&rtc_date_time);
	/*
	printf("time: %02d:%02d:%02d\r\n",rtc_date_time.time.hour,rtc_date_time.time.min,rtc_date_time.time.sec);
	printf("date: %02d / %02d / %04d\r\n",rtc_date_time.date.day,rtc_date_time.date.month,rtc_date_time.date.year);
	*/
}
void setup_lcd()
{
	/*
	if you want to use this display in 4bit mode and save 4 pins , use this line
	*/
	Liquid_Crystal_setup(&lcd1602,LCD_4BITMODE,
	LCD_RS,LCD_WR,LCD_EN,Data_pin_4,Data_pin_5,Data_pin_6,Data_pin_7,0,0,0,0);
	
	/*setup the library's pins, and bit mode in 8 bit mode
	Liquid_Crystal_setup(&lcd1602,LCD_8BITMODE,
	LCD_RS,LCD_WR,LCD_EN,Data_pin_0,Data_pin_1,Data_pin_2,Data_pin_3,Data_pin_4,Data_pin_5,Data_pin_6,Data_pin_7);
	*/
	/*set the columns and rows of the display , here 16 x 2 */
	Liquid_Crystal_initi(&lcd1602,16,2);
	Liquid_Crystal_clear(&lcd1602);
	delay_ms(100);
	/*set the cursor to 0,0 */
	Liquid_Crystal_setCursor(&lcd1602,0,1);
	Liquid_Crystal_writeString(&lcd1602,(char *)"Date:");
	Liquid_Crystal_setCursor(&lcd1602,0,0);
	Liquid_Crystal_writeString(&lcd1602,(char *)"Time:");
}
int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	init_RTC_function();
	/*remove this line and set your own time/date */
	write_RTC_function();
	setup_lcd();
	/* Replace with your application code */
	while (1) 
	{
		read_RTC_function();
		sprintf(Time_string,"%02d:%02d:%02d",rtc_date_time.time.hour,rtc_date_time.time.min,rtc_date_time.time.sec);
		sprintf(Date_string,"%02d/%02d/%04d",rtc_date_time.date.day,rtc_date_time.date.month,rtc_date_time.date.year);
		Liquid_Crystal_setCursor(&lcd1602,6,0);
		Liquid_Crystal_writeString(&lcd1602,Time_string);
		Liquid_Crystal_setCursor(&lcd1602,6,1);
		Liquid_Crystal_writeString(&lcd1602,Date_string);
		delay_ms(1000);
	}
}
