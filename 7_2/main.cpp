#include <iostream>
#include <fstream>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include "pthread_spinlock_osx.h"

void *thread_mtx(void *arg) {
	pthread_mutex_lock((pthread_mutex_t *)arg);
	std::cout << "mutex" << std::endl;

	return NULL;
}

void *thread_spin(void *arg) {
	pthread_spin_lock((pthread_spinlock_t *)arg);
	std::cout << "spin lock" << std::endl;

	return NULL;
}

void *thread_wr(void *arg) {
	pthread_rwlock_wrlock((pthread_rwlock_t *)arg);
	std::cout << "wr lock" << std::endl;

	return NULL;
}

void *thread_rd(void *arg) {
	pthread_rwlock_rdlock((pthread_rwlock_t *)arg);
	std::cout << "rd lock" << std::endl;

	return NULL;
}


int main(int argc, char **argv) {
	std::ofstream f("main.pid");
	f << getpid() << std::flush;
	f.close();

	pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	pthread_spinlock_t s_lock;
	pthread_spin_init(&s_lock, PTHREAD_PROCESS_PRIVATE);
	pthread_rwlock_t wr_lock = PTHREAD_RWLOCK_INITIALIZER;
	pthread_rwlock_t rd_lock = PTHREAD_RWLOCK_INITIALIZER;

	pthread_mutex_lock(&mtx);
	pthread_spin_lock(&s_lock);
	pthread_rwlock_wrlock(&wr_lock);
	pthread_rwlock_wrlock(&rd_lock);

	pthread_t th_id[4];
	pthread_create(&th_id[0], NULL, &thread_mtx, &mtx);
	pthread_create(&th_id[1], NULL, &thread_spin, &s_lock);
	pthread_create(&th_id[2], NULL, &thread_wr, (void *)&wr_lock);
	pthread_create(&th_id[3], NULL, &thread_rd, &rd_lock);

	std::cout << "..." << std::endl;
	sleep(2);

	pthread_mutex_unlock(&mtx);
	pthread_spin_unlock(&s_lock);
	pthread_rwlock_unlock(&wr_lock);
	pthread_rwlock_unlock(&rd_lock);

	pthread_mutex_destroy(&mtx);
	pthread_spin_destroy(&s_lock);
	pthread_rwlock_destroy(&wr_lock);
	pthread_rwlock_destroy(&rd_lock);

	void *ans;
	for(int i = 0; i < 4; i++)
		pthread_join(th_id[i], &ans);
	
	return 0;
}
