/*
 * Copyright (c) 2016 Mieszko Mazurek
 */

#ifndef __ROBOT_H
#define __ROBOT_H

typedef void (*proc_t) (void);

enum movement
{
	STOP,
	FORWARD,
	BACKWARD
};

enum color
{
	LIGHT,
	DARK
};

extern volatile unsigned char	analog_input [8];

extern volatile enum movement	engine_l;
extern volatile enum movement	engine_r;
extern volatile enum color	color_l;
extern volatile enum color	color_r;

void		set_position	(unsigned	y,
				 unsigned	x);
void		clear_screen	(void);
void		clear_chars	(unsigned	n);
unsigned	get_x		(void);
unsigned	get_y		(void);
void		put_char	(char		c);
void		put_string	(const char*	str);
void		put_int		(int		n);
void		put_uint	(unsigned 	n);
void		put_long	(long		n);
void		put_ulong	(unsigned long	n);
unsigned long	get_time	(void);
char		get_random	(void);
void		delay		(unsigned 	millis);
void		run_thread	(proc_t		func,
				 unsigned	size);

#endif
