/*
 * Copyright (c) 2016 Mieszko Mazurek
 */

#include "lib/inc/core/system.h"
#include "lib/inc/core/thread.h"
#include "lib/inc/core/mutex.h"
#include "lib/inc/core/task.h"
#include "lib/inc/core/memalloc.h"
#include "lib/inc/core/panic.h"
#include "lib/inc/drivers/hd44780gpio.h"
#include "lib/inc/drivers/hd44780lcd.h"
#include "lib/inc/drivers/ostream.h"
#include "lib/inc/hardware/gpio.h"
#include "lib/inc/hardware/adc.h"

#include "robot.h"

#include <avr/io.h>

volatile unsigned char 	analog_input [8];

volatile enum movement	engine_l = STOP;
volatile enum movement	engine_r = STOP;

volatile enum color	color_l;
volatile enum color	color_r;

extern void	start		(void);

static void	robot_thread	(void*);

static hd44780lcd_t*	lcd;

int main (void)
{
	hd44780gpio_t*	lcditf;

	system_init ();

	DDRA  = 0xA0;
	PORTA = 0x00;
	DDRC  = 0xff;
	PORTC = 0x00;
	DDRD  = 0xff;
	PORTD = 0x00;

	lcditf = hd44780gpio_new (GPIO_PIND6, GPIO_PINA0, GPIO_PIND7,
				  GPIO_PINC0, GPIO_PINC1, GPIO_PINC2, GPIO_PINC3,
				  GPIO_PINC4, GPIO_PINC5, GPIO_PINC6, GPIO_PINC7);
	lcd = hd44780lcd_new ((hd44780itf_t*) lcditf, INTERFACE_MODE_8BIT, LCD4X20);

	hd44780lcd_clear (lcd);
	hd44780lcd_set_position (lcd, 0, 0);

	TCCR1A = 0xA3;
	TCCR1B = 0x0C; 

	thread_run_alloc (robot_thread, NULL, "robot", 30);

	system_sleep (100);
	start ();
	thread_kill ();
}

void panic (error_t err)
{

}



void set_position (unsigned y, unsigned x)
{
	hd44780lcd_set_position (lcd, y, x);
}

void clear_screen (void)
{
	hd44780lcd_clear (lcd);
}

void clear_chars (unsigned n)
{
	uint8_t y = hd44780lcd_get_y (lcd);
	uint8_t x = hd44780lcd_get_x (lcd);
	while (n--)
		hd44780lcd_put_char (lcd, ' ');
	hd44780lcd_set_position (lcd, y, x);
}

unsigned get_x (void)
{
	return hd44780lcd_get_x (lcd);
}

unsigned get_y (void)
{
	return hd44780lcd_get_y (lcd);
}

void put_char (char c)
{
	ostream_put_char (OSTREAM (lcd), c);
}

void put_string (const char* str)
{
	ostream_put_string (OSTREAM (lcd), str);
}

void put_int (int i)
{
	ostream_put_int (OSTREAM (lcd), i);
}

void put_uint (unsigned i)
{
	ostream_put_int (OSTREAM (lcd), i);
}

void put_long (long l)
{
	ostream_put_int32 (OSTREAM (lcd), l);
}

void put_ulong (unsigned long l)
{
	ostream_put_uint32 (OSTREAM (lcd), l);
}

unsigned long get_time (void)
{
	return system_get_time ();
}

char get_random (void)
{
	return system_rand ();
}

void delay (unsigned delay)
{
	system_sleep (delay);
}

#define STOP_L		82
#define STOP_R		77
#define FORWARD_L	(STOP_L+20)
#define FORWARD_R	(STOP_R-20)
#define BACKWARD_L	(STOP_L-20)
#define BACKWARD_R	(STOP_L+20)

#define COLOR_PARTITION	40

static void robot_thread (void* obj)
{
	static enum movement state_l = !STOP;
	static enum movement state_r = !STOP;

	while (1) {
		for (unsigned char i = 0; i < 8; i++)
			analog_input [i] = adc_read (i);

		uint8_t color_lvalue = adc_read (4);
		uint8_t color_rvalue = adc_read (3);

		color_l = color_lvalue > COLOR_PARTITION ?
			LIGHT : DARK;

		color_r = color_rvalue > COLOR_PARTITION ?
			LIGHT : DARK;

		if (engine_l != state_l) {
			state_l = engine_l;

			switch (state_l) {
			case FORWARD:
				OCR1B = FORWARD_L;
				break;
			case BACKWARD:
				OCR1B = BACKWARD_L;
				break;
			default:
				OCR1B = STOP_L;
			}
		}

		if (engine_r != state_r) {
			state_r = engine_r;

			switch (state_r) {
			case FORWARD:
				OCR1A = FORWARD_R;
				break;
			case BACKWARD:
				OCR1A = BACKWARD_R;
				break;
			default:
				OCR1A = STOP_R;
			}
		}
	}
}
