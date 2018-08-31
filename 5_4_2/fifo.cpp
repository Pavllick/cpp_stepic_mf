#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
	const char *in = "in.fifo";
	const char *out = "out.fifo";

	std::ofstream in_create(in);
	std::ofstream out_create(out);
	in_create.close();
	out_create.close();

	mkfifo(in, 0666);
	mkfifo(out, 0666);

	char buf[1024];
	for(;;) {
			bzero(buf, sizeof(buf));

			int in_rd = open(in, O_RDONLY);
			read(in_rd, buf, sizeof(buf) - 1);
			close(in_rd);

			int out_wr = open(out, O_WRONLY);
			write(out_wr, buf, strlen(buf) - 1);
			close(out_wr);
		}

	return 0;
}
