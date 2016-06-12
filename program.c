/*
 * Copyright (c) 2016 Mieszko Mazurek
 */

#include "robot.h"

void loop (void)
{
	engine_l = FORWARD;
	engine_r = FORWARD;
	while (color_l == DARK && color_r == DARK);

	engine_l = STOP;
	engine_r = STOP;

	engine_l = BACKWARD;
	while (color_l == DARK && color_r == LIGHT);
	engine_l = STOP;

	engine_r = BACKWARD;
	while (color_l == LIGHT && color_r == DARK);
	engine_r = STOP;

	engine_l = BACKWARD;
	engine_r = BACKWARD;

	delay (1000);

	engine_l = STOP;
	engine_r = STOP;

	if (get_random () & 1) {
		engine_l = FORWARD;
		engine_r = BACKWARD;
	} else {
		engine_l = BACKWARD;
		engine_r = FORWARD;
	}

	delay (1200);

	engine_l = STOP;
	engine_r = STOP;

	delay (250);
}

void print_color (void)
{
	while (1) {
		set_position (0, 0);
		clear_chars (5);
		put_string (color_l == LIGHT ? "LIGHT" : "DARK");
		set_position (1, 5);
		clear_chars (3);
		put_int (analog_input [4]);

		if (color_r == DARK) {
			set_position (0, 15);
			clear_chars (5);
			set_position (0, 16);
			put_string ("DARK");
		} else {
			set_position (0, 15);
			clear_chars (5);
			put_string ("LIGHT");
		}

		set_position (1, 12);
		clear_chars (3);
		put_int (analog_input [3]);

		delay (100);
	}
}

void start (void)
{
	run_thread (print_color, 80);
	while (1)
		loop ();
}
