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
	write(sock, buf, 0);
	memset(buf, 0, 80);
	read(sock, buf, 80);
	
    moveCircle(buf, sock);

}

int moveCircle(char buf[80], int sock)
{
	int degrees = 0;
	int degrees_two = 0;

	sprintf(buf, "S MEL");
    write(sock, buf, strlen(buf));
    memset(buf, 0, 80);
	read(sock, buf, 80);

	sscanf(buf, "S MEL %d\n", &degrees_two);
	printf("%i\n", degrees_two);

	while(degrees < (degrees_two + 2000))
	{
		sprintf(buf, "S MEL");
    	write(sock, buf, strlen(buf));
    	memset(buf, 0, 80);
		read(sock, buf, 80);

		sscanf(buf, "S MEL %d\n", &degrees);

    	sprintf(buf, "M L 20\n");
		write(sock, buf, strlen(buf));
		memset(buf, 0, 80);
		read(sock, buf, 80);
	}

}
