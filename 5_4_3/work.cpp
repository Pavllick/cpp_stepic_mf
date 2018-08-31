#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int sv[2];
	socketpair(AF_UNIX, SOCK_STREAM, 0, sv);

	if(!fork()) {
		for(;;) {
			int ac = accept(sv[0], NULL, NULL);
			close(ac);
		}
	} else {
		for(;;) {
			int ac = accept(sv[1], NULL, NULL);
			close(ac);
		}
	}

	return 0;
}
