#include <iostream>
#include <fstream>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
// #include <sys/msg.h>
#include <sys/sem.h>

/* union semun {  // for linux
    int val;
    struct semid_ds *buf;
    undigned short *array;
};*/

int main(int argc, char **argv) {
	key_t key = ftok("/tmp/sem.temp", 1);
	int sem;
	if((sem = semget(key, 0, 0)) == -1)
		sem = semget(key, 16, 0666 | IPC_CREAT);
	else {
		semctl(key, 0, IPC_RMID);
		sem = semget(key, 16, 0666 | IPC_CREAT);
	}
	std::cout << "sem id: " << sem << std::endl;
	
	unsigned short semvals[16];
	for(int i = 0; i < 16; i++)
		semvals[i] = i;

	union semun smu;
	smu.array = semvals;
	std::cout << semctl(sem, 0, SETALL, smu) << std::endl;

	// semctl(sem, 0, IPC_RMID);

	return 0;
}
