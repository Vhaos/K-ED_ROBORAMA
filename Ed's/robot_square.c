#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
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

	sleep(1);
    drawSquare(buf, sock);

	
	return 0;
}

int turnclockwise(int speed, int degrees, char buf[80], int sock)
{

		sprintf(buf, "M L %d", -speed);
		write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		sprintf(buf, "M R %d", speed);
		write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		usleep(100000);

}

int drawSquare(char buf[80], int sock)
{
	moveforward(20, 20, buf, sock);
    turnNinety(10, buf, sock);
    moveforward(20, 20, buf, sock);
    turnNinety(10, buf, sock);
    moveforward(20, 20, buf, sock);
    turnNinety(10, buf, sock);
    moveforward(20, 20, buf, sock);
    turnNinety(10, buf, sock);
}

int moveforward(int speed, int h, char buf[80], int sock)
{
		int i;

		for (i = 0; i < h ; i++)
		{
       
		sprintf(buf, "M LR %d %d", speed, speed);
		write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		sprintf(buf, "M R %d", speed);
		write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		usleep(100000);
		
		}
}

int turnNinety(int speed, char buf[80], int sock)
{   
	int degrees = 0;
	int degrees_two = 0;

	sprintf(buf, "S MEL");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
	read(sock, buf, 80);

	sscanf(buf, "S MEL %d\n", &degrees_two);
	//printf("%i\n", degrees_two);

    while (degrees < (degrees_two + 215))
    {
    	sprintf(buf, "S MEL");
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		sscanf(buf, "S MEL %d\n", &degrees);
		//printf("%i\n", degrees);

        sprintf(buf, "M LR %d %d\n", speed, -speed);
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);
     }
}