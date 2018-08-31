#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
// #include <regex>
// #define REGEX
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>

int set_nonblock(int fd) {
	int flags;
#if defined(O_NONBLOCK)
	if(-1 == (flags = fcntl(fd, F_GETFL, 0)))
		flags = 0;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
	flags = 1;
	return ioctl(fd, FIOBIO, &flags);
#endif
}

std::string exec_in_pipe(std::pair<std::string, std::string> prog, std::string in) {
	int pfd_in[2], pfd_out[2];
	pipe(pfd_in);
	pipe(pfd_out);

	if(!fork()) {
		close(pfd_in[1]);
		close(pfd_out[0]);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);

		dup2(pfd_in[0], STDIN_FILENO);
		dup2(pfd_out[1], STDOUT_FILENO);

		if(prog.second != "")
			execlp(prog.first.c_str(), prog.first.c_str(), prog.second.c_str(), NULL);
		else
			execlp(prog.first.c_str(), prog.first.c_str(), NULL);
	}

	close(pfd_in[0]);
	close(pfd_out[1]);

	const char *msg = in.c_str();
	write(pfd_in[1], msg, in.size());
	close(pfd_in[1]);

	char buf[1024];
	bzero(&buf, sizeof(buf));

	read(pfd_out[0], buf, sizeof(buf));
	
	return std::string(buf);
}
 
void exec_str(std::vector<std::pair<std::string, std::string>> progs) {
	std::string res("");
	for(auto p = progs.begin(); p != progs.end(); p++)
		res = exec_in_pipe(*p, res);

	// std::cout << res << std::endl;

	std::ofstream f("/home/box/result.out");
	f << res;
	f.close();
}

std::vector<std::pair<std::string, std::string>> parse_find(std::string str_buf) {
	std::vector<std::pair<std::string, std::string>> progs;
	
	while(str_buf != "") {
		std::size_t mat = 0;
		std::pair<std::string, std::string> cmd;

		std::string full_ss;
		mat = str_buf.find("|");
		if(mat == std::string::npos) {
			full_ss = str_buf;
			str_buf = "";
		} else {
			full_ss = str_buf.substr(0, mat);
			str_buf = str_buf.substr(mat + 1);
		}

		while(full_ss[0] == ' ')
			full_ss = full_ss.substr(1);

		while(full_ss[full_ss.size() - 1] == ' ')
			full_ss = full_ss.substr(0, full_ss.size() - 1);

		mat = full_ss.find(" ");
		if(mat == std::string::npos) {
			cmd.first = full_ss;
			cmd.second = "";
		}	else {
			cmd.first = full_ss.substr(0, mat);
			cmd.second = full_ss.substr(mat + 1);
		}

		progs.push_back(cmd);
	}

	return progs;
}

#ifdef REGEX
std::vector<std::pair<std::string, std::string>> parse_regex(std::string str_buf) {
	std::vector<std::pair<std::string, std::string>> progs;
	std::regex expr(R"((\w+)[\s]?(([\s]*([-]?(?:\.\/)?\w+))*)?[\s|]?)");
	
	std::smatch m;
	while(std::regex_search(str_buf, m, expr)) {
		progs.push_back(std::make_pair(m.str(1), m.str(2)));
		str_buf = m.suffix();
	}

	return progs;
}
#endif

int main(int argc, char **argv) {
	char buf[1024];
	
	set_nonblock(STDIN_FILENO);
	int r_size = read(STDIN_FILENO, buf, sizeof(buf) - 1);
	buf[r_size - 1] = 0x00;
	std::string str_buf(buf);

	std::vector<std::pair<std::string, std::string>> progs;
#ifdef REGEX
	progs = parse_regex(str_buf);
#else
	progs = parse_find(str_buf);
#endif
	
	for(auto a: progs)
		std::cout << a.first << " : " << a.second << "'" << std::endl;

	exec_str(progs);

	return 0;
}
