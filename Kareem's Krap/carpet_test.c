#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "picomms.h"

void carpet_test(int);

int main() 
{
	set_asr(0);
	carpet_test(50);
	return 0;
} 

void carpet_test(int speed)
{
	set_motors(speed,speed);

	int left_distance, right_distance;
	get_motor_encoders(&left_distance, &right_distance);

	while(right_distance > left_distance)
	{
		set_motors(speed + 10, speed);
	}

	while(left_distance > right_distance)
	{
		set_motors(speed, speed + 10);
	}

	carpet_test(speed);
}