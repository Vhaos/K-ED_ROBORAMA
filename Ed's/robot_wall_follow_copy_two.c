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
	set_ir_angle(1, -45);
	//int ultra = get_us_dist();

	if (right_distance < 40)
	{
		while (right_distance < 40)
		{
			get_front_ir_dists(&left_distance, &right_distance);
			set_motors(speed, 5); //(20, -10)
		}
	}
	else if (right_distance > 60 && left_distance > 60)
	{
		set_ir_angle(0, -45);
		//set_motors(0,0);
		get_front_ir_dists(&left_distance, &right_distance);

		if (left_distance < 60)
		{
			set_ir_angle(0, 0);
			get_front_ir_dists(&left_distance, &right_distance);
			if (left_distance >= 30)
			{
				while (left_distance >= 30)
				{
					printf("%i\n", left_distance);
					get_front_ir_dists(&left_distance, &right_distance);
					set_motors(10, 30); //(-10, 20)
				}
			}
			else if (left_distance < 40 && left_distance > 20)
			{
				while (left_distance < 40 && left_distance > 20)
				{
					get_front_ir_dists(&left_distance, &right_distance);
					set_motors(speed, speed);
				}
			}
			else 
			{
				while (left_distance < 20)
				{
					printf("%i\n", left_distance);
					get_front_ir_dists(&left_distance, &right_distance);
					set_motors(speed, 10); //(20, -10)
				}
			}
		}
		else
		{
			int i = 0;
			for(i = 0; i < 1; i++)
			{
				set_motors(speed, speed);
				sleep(1);
			}
			while ( left_distance > 40)
			{
				get_front_ir_dists(&left_distance, &right_distance);
				set_motors(10, speed); //(-10, 20)
			}
			set_ir_angle(0, 0);
		}
		//set_ir_angle(0, 0);
	}
	else if (left_distance >= 40)
	{
		while (left_distance >= 40)
		{
			get_front_ir_dists(&left_distance, &right_distance);
			set_motors(10, speed); //(-10, 20)
		}
	} //Original 40 and 35
	else if (left_distance <= 20)
	{
		while (left_distance <= 20)
		{
			get_front_ir_dists(&left_distance, &right_distance);
			set_motors(speed, 10); //(20, -10)
		}
	}
	else if (left_distance > 20 && left_distance < 40)
	{
		get_front_ir_dists(&left_distance, &right_distance);
		set_motors(speed, speed);
	}

	{
		get_front_ir_dists(&left_distance, &right_distance);
		set_motors(speed, speed);
	}

	wall_follow(speed);
}