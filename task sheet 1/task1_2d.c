//By Ed Collins and Kareem Daggash


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

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
	sleep(1);

	make_star(buf, sock);

	return 0;
}

int turn(int speed, int time, char buf[80], int sock)
{
	int i;

	for (i = 0; i < time ; i++)
	{

        sprintf(buf, "M LR %d %d\n", speed, -speed);
    	write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		usleep(100000);
	}
}

int moveforward(int speed, int time, char buf[80], int sock)
{
		int i;

		for (i = 0; i < time ; i++)
		{
		sprintf(buf, "C TRAIL\n");
		write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		sprintf(buf, "M LR %d %d", speed, speed);
		write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);

		usleep(100000);
		}
}

int make_star(char buf[80], int sock)
{
	int i;
	for(i = 0; i<5; i++)
	{
	moveforward(20, 20, buf, sock);
    turn(5, 61, buf, sock);
	}
}