/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

void delay_example(void)
{
	delay_ms(5000);
}

/**
 * Example of using CALENDAR_0.
 */
static struct calendar_alarm alarm;

static void alarm_cb(struct calendar_descriptor *const descr)
{
	/* alarm expired */
}

void CALENDAR_0_example(void)
{
	struct calendar_date date;
	struct calendar_time time;

	calendar_enable(&CALENDAR_0);

	date.year  = 2000;
	date.month = 12;
	date.day   = 31;

	time.hour = 12;
	time.min  = 59;
	time.sec  = 59;

	calendar_set_date(&CALENDAR_0, &date);
	calendar_set_time(&CALENDAR_0, &time);

	alarm.cal_alarm.datetime.time.sec = 4;
	alarm.cal_alarm.option            = CALENDAR_ALARM_MATCH_SEC;
	alarm.cal_alarm.mode              = REPEAT;

	calendar_set_alarm(&CALENDAR_0, &alarm, alarm_cb);
}
