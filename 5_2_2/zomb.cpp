#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <fstream>

void h_int(int par) {
	std::cout << "Quit proces int" << std::endl;
}

void h_term(int par) {
	std::cout << "Quit proces term" << std::endl;
}

int main(int argc, char **argv) {
	std::ofstream f("pid_parent");
	f << getpid();
	f.close();

	int c_pid;
	int stat;
	c_pid = fork();
	if(c_pid == 0) {
		std::ofstream f("pid_child");
		f << getpid();
		f.close();

		pause();
	} else {
		std::cout << waitpid(c_pid, &stat, 0) << std::endl;
	}
	
	return 0;
}
