/*
 * Copyright (c) 2016 Mieszko Mazurek
 */

#include "avrmeos/inc/system.h"
#include "avrmeos/inc/thread.h"
#include "avrmeos/inc/mutex.h"
#include "avrmeos/inc/gpio.h"
#include "avrmeos/inc/hd44780gpio.h"
#include "avrmeos/inc/hd44780lcd.h"
#include "avrmeos/inc/task.h"
#include "avrmeos/inc/memalloc.h"
#include "avrmeos/inc/ostream.h"

#include "robot.h"

#include <avr/io.h>

extern void 	init_system 	(void) __attribute__ ((naked));
extern void	start		(void);

static void		engine0_set	(int);
static void		engine1_set	(int);
static int	engine0_get	(void);
static int	engine1_get	(void);


struct engine engine_left = {
	.set = engine0_set,
	.get = engine0_get,
};

struct engine engine_right = {
	.set = engine1_set,
	.get = engine1_get,
};

static hd44780lcd_t*	lcd;

int main (void)
{
	hd44780gpio_t*	lcditf;

	init_system ();

	DDRA  = 0xA0;
	PORTA = 0x00;
	DDRC  = 0xff;
	PORTC = 0x00;
	DDRD  = 0xff;
	PORTD = 0x00;

	lcditf = hd44780gpio_new (GPIO_PIND6, GPIO_PINA0, GPIO_PIND7,
				  GPIO_PINC0, GPIO_PINC1, GPIO_PINC2, GPIO_PINC3,
				  GPIO_PINC4, GPIO_PINC5, GPIO_PINC6, GPIO_PINC7);
	lcd = hd44780lcd_new ((hd44780itf_t*) lcditf, LCD4X20);

	hd44780lcd_set_position (lcd, 0, 0);

	TCCR1A = 0xA3;
	TCCR1B = 0x0C;

	system_sleep (500);
	start ();

	thread_kill ();
}

void gotoxy (unsigned x, unsigned y)
{
	hd44780lcd_set_position (lcd, y, x);
}

void clrscr (void)
{
	hd44780lcd_clear (lcd);
}

unsigned getx (void)
{
	return hd44780lcd_get_x (lcd);
}

unsigned gety (void)
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

void sleep (unsigned delay)
{
	system_sleep (delay);
}

#define ENGINE0_STOP		77
#define ENGINE1_STOP		82


static void engine0_set (int p)
{
	OCR1B = p;
}

static void engine1_set (int p)
{
	OCR1A = p;
}

static int engine0_get (void)
{
	return OCR1B;
}

static int engine1_get (void)
{
	return OCR1A;
}
