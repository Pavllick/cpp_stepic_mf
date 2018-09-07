#include <iostream>
#include <fstream>

#include <pthread.h>
#include <unistd.h>

#include "pthread_barrier_osx.h"

struct Cond_wait {
	pthread_cond_t cond;
	pthread_mutex_t mtx;
};

void *thread_cond(void *arg) {
	pthread_cond_wait(&((Cond_wait *)arg)->cond, &((Cond_wait *)arg)->mtx);
	std::cout << "cond end waiting" << std::endl;

	return NULL;
}

void *thread_bar(void *arg) {
	pthread_barrier_wait((pthread_barrier_t *)arg);
	std::cout << "barrier end waiting" << std::endl;
	
	return NULL;
}


int main(int argc, char **argv) {
	std::ofstream f("main.pid");
	f << getpid() << std::flush;
	f.close();

	Cond_wait *cw = new Cond_wait;
	cw->cond = PTHREAD_COND_INITIALIZER;
	cw->mtx = PTHREAD_MUTEX_INITIALIZER;

	pthread_barrier_t br;
	pthread_barrier_init(&br, NULL, 2);

	pthread_t thd[2];
	pthread_create(&thd[0], NULL, &thread_cond, (void *)cw);
	pthread_create(&thd[0], NULL, &thread_bar, (void *)&br);

	std::cout << "sleep in main thread" << std::endl;
	sleep(2);
	pthread_cond_broadcast(&cw->cond);
	pthread_barrier_wait(&br);

	void *ans;
	pthread_join(thd[0], &ans);
	pthread_join(thd[1], &ans);

	pthread_mutex_destroy(&cw->mtx);
	pthread_cond_destroy(&cw->cond);
	delete cw;

	pthread_barrier_destroy(&br);

	return 0;
}
