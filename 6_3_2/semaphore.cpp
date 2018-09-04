#include <iostream>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

int main(int argc, char **argv) {
	sem_unlink("/test.sem");
	sem_t *sem = sem_open("/test.sem", O_CREAT, 0666, 66);

	return 0;
}
