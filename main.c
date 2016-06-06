/*
 * Copyright (c) 2016 Mieszko Mazurek
 */

#include "robot.h"

void start (void)
{
	unsigned char v = 0;

	engine_left.set (82);
	engine_right.set (0);


	clrscr ();

	gotoxy (0, 0);
	put_string ("hello world");

	while (1) {
		engine_right.set (v++);

		gotoxy (0, 1);
		put_string ("   ");
		gotoxy (0, 1);
		put_int (engine_right.get ());

		sleep (100);
	}
}
