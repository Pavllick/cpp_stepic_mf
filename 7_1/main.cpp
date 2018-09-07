#include <iostream>
#include <fstream>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void *thread(void *arg) {
	std::ofstream f("main.pid");
	f << getpid() << std::flush;
	f.close();

	++*(uint32_t *)arg;
	++*(uint32_t *)arg;
	return arg;
}

int main(int argc, char **argv) {
	std::cout << getpid() << std::endl;

	pthread_t th_id;
	uint32_t arg = 4;
	void *ans;
	std::cout << arg << std::endl;
	
	pthread_create(&th_id, NULL, &thread, &arg);
	pthread_join(th_id, &ans);
	
	std::cout << *(uint32_t *)ans << std::endl;

	return 0;
}
