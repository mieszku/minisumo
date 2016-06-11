/*
 * Copyright (c) 2016 Mieszko Mazurek
 */

#include "robot.h"

void start (void)
{
	engine_l = FORWARD;
	clear_screen ();
	set_position (0, 0);
	put_string ("left forward");
	delay (1500);

	engine_l = BACKWARD;
	clear_screen ();
	set_position (0, 0);
	put_string ("left backward");
	delay (1500);

	engine_l = STOP;
	engine_r = STOP;
	clear_screen ();
	set_position (0, 0);
	put_string ("both stop");
	delay (4000);

	engine_r = FORWARD;
	clear_screen ();
	set_position (0, 0);
	put_string ("right forward");
	delay (1500);

	engine_r = BACKWARD;
	clear_screen ();
	set_position (0, 0);
	put_string ("right backward");
	delay (1500);

	engine_l = STOP;
	engine_r = STOP;
	clear_screen ();
	set_position (0, 0);
	put_string ("both stop");
}
