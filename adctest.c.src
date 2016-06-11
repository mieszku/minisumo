/*
 * Copyright (c) 2016 Mieszko Mazurek
 */

#include "robot.h"

void start (void)
{
	while (1) {
		set_position (0, 0);
		put_string ("ain 0: ");
		clear_chars (3);
		put_uint (analog_input [0]);
		set_position (0, 10);
		put_string ("ain 1: ");
		clear_chars (3);
		put_uint (analog_input [1]);

		set_position (1, 0);
		put_string ("ain 2: ");
		clear_chars (3);
		put_uint (analog_input [2]);
		set_position (1, 10);
		put_string ("ain 3: ");
		clear_chars (3);
		put_uint (analog_input [3]);

		set_position (2, 0);
		put_string ("ain 4: ");
		clear_chars (3);
		put_uint (analog_input [4]);
		set_position (2, 10);
		put_string ("ain 5: ");
		clear_chars (3);
		put_uint (analog_input [5]);

		set_position (3, 0);
		put_string ("ain 6: ");
		clear_chars (3);
		put_uint (analog_input [6]);
		set_position (3, 10);
		put_string ("ain 7: ");
		clear_chars (3);
		put_uint (analog_input [7]);

		delay (200);
	}
}
