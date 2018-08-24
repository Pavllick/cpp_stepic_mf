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
	std::ofstream f("pid");
	f << getpid();
	f.close();
	
	signal(SIGTERM | SIGINT, SIG_IGN);
	// signal(SIGINT, h_int);
	// signal(SIGTERM, h_term);
	pause();

	return 0;
}
