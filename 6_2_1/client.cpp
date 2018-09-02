#include <iostream>
#include <fstream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char **argv) {
	const char *lp_name = "msg.temp";
	std::ofstream l_point(lp_name);
	l_point.close();

	key_t mq_key = ftok(lp_name, 1);
	int sv_mq = msgget(mq_key, 0666);
	std::cout << "key: " << mq_key << "; mq: " << sv_mq << std::endl;

	struct {
    long mtype;
    char mtext[80];
	} msg;
	
	msg.mtype = 2;
	strcpy(msg.mtext, "test text");
	msgsnd(sv_mq, &msg, 80, 0);

	return 0;
}
