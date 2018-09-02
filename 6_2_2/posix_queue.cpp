#include <iostream>
#include <fstream>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h> // Only for POSIX compatible systems, doesn't on OSX

int main(int argc, char **argv) {
	const char *lp_name = "/test.mq";
	mq_unlink(lp_name);

	const int msg_size = 1024;
	struct mq_attr attr;
	attr.mq_maxmsg = 10;
	attr.mq_flags = 0;
	attr.mq_msgsize = msg_size;
	mqd_t mq_fd = mq_open(lp_name, O_CREAT | O_RDWR, 0666, &attr);

	char buf[msg_size];
	mq_receive(mq_fd, buf, msg_size, 0);
	mq_close(mq_fd);

	const char *msg_name = "message.txt";
	std::cout << buf << std::endl;
	std::ofstream resp_msg(msg_name);
	resp_msg.write(buf, strlen(buf) - 1);
	resp_msg.close();
	
	return 0;
}
