#include <iostream>
#include <cstdint>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {

	int mem_size = 1024 * 1024;
	int shm_fd = shm_open("/test.shm", O_RDWR | O_CREAT, 0666);
	std::cout << ftruncate(shm_fd, mem_size) << std::endl;
	int8_t *const mem_b = (int8_t *)mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	if(*mem_b == -1) {
		std::cout << "mem_b error" << std::endl;
		return 0;
	}

	int8_t val = 13;
	for(int i = 0; i < mem_size; i++)
		*(mem_b + i) = val;

	std::cout << (*(mem_b + 1023) == val) << std::endl;

	munmap((void *)mem_b, mem_size);
	shm_unlink("/test.shm");
	
	return 0;
}
