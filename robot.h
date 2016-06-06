/*
 * Copyright (c) 2016 Mieszko Mazurek
 */

#ifndef __ROBOT_H
#define __ROBOT_H

void		gotoxy		(unsigned	x,
				 unsigned	y);
void		clrscr		(void);
unsigned	getx		(void);
unsigned	gety		(void);
void		put_char	(char		c);
void		put_string	(const char*	str);
void		put_int		(int		n);
void		put_uint	(unsigned	n);
void		put_long	(long		n);
void		put_ulong	(unsigned long	n);
unsigned long	get_time	(void);
void		sleep		(unsigned	delay);

struct engine
{
	void	(*set)	(int);
	int	(*get)	(void);
};

extern struct engine	engine_left;
extern struct engine	engine_right;

#endif
