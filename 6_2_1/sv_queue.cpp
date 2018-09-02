#include <iostream>
#include <fstream>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char **argv) {
	const char *lp_name = "msg.temp";
	std::ofstream l_point(lp_name);
	l_point.close();

	key_t mq_key = ftok(lp_name, 1);
	int sv_mq = msgget(mq_key, IPC_CREAT | 0666);
	std::cout << "key: " << mq_key << "; mq: " << sv_mq << std::endl;

	struct {
    long mtype;
    char mtext[256];
	} msg;
	
	msgrcv(sv_mq, &msg, 256, 0, 0);
	msgctl(sv_mq, IPC_RMID, NULL);

	const char *msg_name = "message.txt";
	std::ofstream resp_msg(msg_name);
	resp_msg.write(msg.mtext, strlen(msg.mtext) - 1);
	resp_msg.close();
	
	return 0;
}
