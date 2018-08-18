#include <iostream>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#ifndef MSG_NOSIGNAL
# define MSG_NOSIGNAL 0
# ifdef SO_NOSIGPIPE
# define CEPH_USE_SO_NOSIGPIPE
# else
# error "Cannot block SIGPIPE!"
# endif
#endif

int main(int argc, char **argv) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(12444);
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	bind(sock, (struct sockaddr *)(&sa), sizeof(sa));

	listen(sock, SOMAXCONN);

	while(true) {
		int slave = accept(sock, nullptr, nullptr);

		char buf[] = {0, 0, 0, 0, 0};
		recv(slave, buf, 4, MSG_NOSIGNAL);
		send(slave, buf, 4, MSG_NOSIGNAL);

		shutdown(slave, SHUT_RDWR);
		close(slave);

		std::cout << buf << std::endl;
	}

	return 0;
}
