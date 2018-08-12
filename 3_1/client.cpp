#include <iostream>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(12444);
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	connect(sock, (struct sockaddr *)(&sa), sizeof(sa));
	char buf[] = "TEST";

	send(sock, buf, 4, SO_NOSIGPIPE);
	recv(sock, buf, 4, SO_NOSIGPIPE);

	shutdown(sock, SHUT_RDWR);

	std::cout << buf << std::endl;

	return 0;
}
