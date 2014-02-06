#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

int clockwise_145(char buf[80], int sock)
{
	int degrees = 0;
	int degrees_two = 0;

	sprintf(buf, "S MEL");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
	read(sock, buf, 80);

	sscanf(buf, "S MEL %d\n", &degrees_two);

    while (degrees < (degrees_two + 400))
    {
    	sprintf(buf, "S MEL");
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		sscanf(buf, "S MEL %d\n", &degrees);

        sprintf(buf, "M LR %d %d\n", 25, -25);
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);
     }
}

int clockwise_115(char buf[80], int sock)
{
	int degrees = 0;
	int degrees_two = 0;

	sprintf(buf, "S MEL");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
	read(sock, buf, 80);

	sscanf(buf, "S MEL %d\n", &degrees_two);

    while (degrees < (degrees_two + 405))
    {
    	sprintf(buf, "S MEL");
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		sscanf(buf, "S MEL %d\n", &degrees);

        sprintf(buf, "M LR %d %d\n", 25, -25);
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);
     }
}

int clockwise_90(char buf[80], int sock)
{   
	int degrees = 0;
	int degrees_two = 0;

	sprintf(buf, "S MEL");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
	read(sock, buf, 80);

	sscanf(buf, "S MEL %d\n", &degrees_two);

    while (degrees < (degrees_two + 355))
    {
    	sprintf(buf, "S MEL");
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		sscanf(buf, "S MEL %d\n", &degrees);

        sprintf(buf, "M LR %d %d\n", 25, -25);
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);
     }
}

int forward(int scale, char buf[80], int sock)
{
	int degrees;
	int speed = 100;

	sprintf(buf, "S MEL");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
	read(sock, buf, 80);

	sscanf(buf, "S MEL %d\n", &degrees);

	int degrees_two = degrees + (36*scale);

     while (degrees < (degrees_two))
    {

    	sprintf(buf, "M LR %d %d\n", speed, speed);
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		degrees++;
     }
}

int hypotenuse(int scale, char buf[80], int sock)
{
	int degrees;
	int speed = 100;

	sprintf(buf, "S MEL");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
	read(sock, buf, 80);

	sscanf(buf, "S MEL %d\n", &degrees);

	int degrees_two = degrees + (48*scale);

     while (degrees < (degrees_two))
    {

    	sprintf(buf, "M LR %d %d\n", speed, speed);
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		degrees++;
     }

}

int main() 
{
	char buf[80];
	struct sockaddr_in s_addr;
	int i, sock;

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		fprintf(stderr, "Failed to create socket\n");
		exit(1);
	}

	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	s_addr.sin_port = htons(55443);

	if (connect(sock, (struct sockaddr *) &s_addr, sizeof(s_addr)) < 0) {
		fprintf(stderr, "Failed to connect socket\n");
		exit(1);
	}

	sleep(3);
	read(sock, buf, 80);
	memset(buf, 0, 80);

	forward(1, buf, sock);
	clockwise_145(buf, sock);
	hypotenuse(1, buf, sock);
	clockwise_115(buf, sock);
	forward(1, buf, sock);
	clockwise_90(buf, sock);

	return 0;
}