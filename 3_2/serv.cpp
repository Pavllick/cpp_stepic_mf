#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <map>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include <sys/event.h>

#ifndef MSG_NOSIGNAL
# define MSG_NOSIGNAL 0
# ifdef SO_NOSIGPIPE
# define CEPH_USE_SO_NOSIGPIPE
# else
# error "Cannot block SIGPIPE!"
# endif
#endif

int set_nonblock(int fd) {
	int flags;
#if defined(O_NONBLOCK)
	if(-1 == (flags = fcntl(fd, F_GETFL, 0)))
		flags = 0;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
	flags = 1;
	return ioctl(fd, FIOBIO, &flags);
#endif
}

int main(int argc, char **argv) {
	int master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(12444);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(master_socket, (struct sockaddr *)(&sa), sizeof(sa));
	set_nonblock(master_socket);
	listen(master_socket, SOMAXCONN);

	int KQueue = kqueue();

	struct kevent KEvent;
	bzero(&KEvent, sizeof(KEvent));
	EV_SET(&KEvent, master_socket, EVFILT_READ, EV_ADD, 0, 0, 0);
	kevent(KQueue, &KEvent, 1, nullptr, 0, nullptr);
	
	std::map<int,  sockaddr> slaves;
	for(;;) {
		bzero(&KEvent, sizeof(KEvent));
		kevent(KQueue, nullptr, 0, &KEvent, 1, nullptr);
		
		if(KEvent.filter & EVFILT_READ) {
			if(KEvent.ident == master_socket) {
				struct sockaddr slave_sa;
				socklen_t size_slave_sa = sizeof(slave_sa);
				int slave_sock = accept(master_socket, &slave_sa, &size_slave_sa);
				set_nonblock(slave_sock);

				bzero(&KEvent, sizeof(KEvent));
				EV_SET(&KEvent, slave_sock, EVFILT_READ, EV_ADD, 0, 0, 0);
				kevent(KQueue, &KEvent, 1, nullptr, 0, nullptr);

				slaves[slave_sock] = slave_sa;
			} else {
				static char buf[1024];
				int resv_size = recv(KEvent.ident, buf, sizeof(buf), MSG_NOSIGNAL);

				if(resv_size <= 0) {
					close(KEvent.ident);
					std::cout << "disconnection" << std::endl;
				} else {
					for(auto &slave: slaves)
						if(slave.first != KEvent.ident) {
							std::stringstream ss;
							ss << inet_ntoa(((struct sockaddr_in*)(&slave.second))->sin_addr) << ":"
								 <<     ntohs(((struct sockaddr_in*)(&slave.second))->sin_port) << " "
								 << buf;

							send(slave.first, ss.str().c_str(), sizeof(ss.str()), MSG_NOSIGNAL);
						}
				}
			}
		}
	}

	return 0;
}
