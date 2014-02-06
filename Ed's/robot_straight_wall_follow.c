#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "picomms.h"

void wall_follow(int);

int main() {

	int speed = 50;
	wall_follow(speed);
	return 0;
}

void wall_follow(int speed)
{
	int left_distance, right_distance, left_side;
	get_front_ir_dists(&left_distance, &right_distance);
	left_side = get_side_ir_dist(0);
	int ultra = get_us_dist();

	if (ultra < 30)
	{
		while (ultra < 30)
		{
			ultra = get_us_dist();
			set_motors(5, -5);
		}
	}
	else if (ultra > 60 && left_distance > 80 && right_distance && 80)
	{
		while (ultra > 35)
		{
			ultra = get_us_dist();
			set_motors(speed, speed);
		}
	}
	else if (left_distance >= 40)
	{
		while (left_distance >= 40)
		{
			get_front_ir_dists(&left_distance, &right_distance);
			set_motors(-5, 5);
		}
	}
	else if (left_distance <= 35)
	{
		while (left_distance <= 35)
		{
			get_front_ir_dists(&left_distance, &right_distance);
			set_motors(5, -5);
		}
	}

	while (left_distance < 40 && left_distance > 20 && ultra > 30) 
	{
		get_front_ir_dists(&left_distance, &right_distance);
		ultra = get_us_dist();
		set_motors(speed, speed);
	}

	wall_follow(speed);
}