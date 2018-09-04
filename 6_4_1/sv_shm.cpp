#include <iostream>
#include <cstdint>

#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv) {
	key_t key = ftok("/tmp/mem.temp", 1);
	int mem_size = 1024 * 1024;
	int shm_fd = shmget(key, mem_size, 0666 | IPC_CREAT);
	int8_t *const mem_b = (int8_t *)shmat(shm_fd, NULL, 0);

	if(*mem_b == -1) {
		std::cout << "mem_b error" << std::endl;
		return 0;
	}

	int8_t val = 42;
	for(int i = 0; i < mem_size; i++)
		*(mem_b + i) = val;

	std::cout << *(mem_b + 1023) << std::endl;
	shmdt((void *)mem_b);
	
	return 0;
}
