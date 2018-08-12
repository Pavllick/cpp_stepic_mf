#include <iostream>
#include <map>
#include <stdlib.h>
#include <regex>
#include <sstream>

std::string derivative(std::string polynomial) {
	std::smatch m;

	std::regex rg(R"((\+|-)?(\d+)*[\*]?[x][\^]*(\d+)?)");

	regex_search(polynomial, m, rg);
	for (auto x : m)
		std::cout << x << "'" << std::endl;
	std::cout << std::endl;

	std::map<int, int> pows;
	while(regex_search(polynomial, m, rg)) {
		int pn = atoi(m.str(2).c_str());
		int pfn = atoi(m.str(3).c_str());
		if(m[1] == "-")
			pn = pn * -1;
		
		if(regex_match(m.str(0), std::regex(R"((\+|-)?(x))"))) {
			if(m.str(0) == "-x")
				pows[0] -= 1;
			else
				pows[0] += 1;
		} else if(m[3] == "" && m[2] != "") {
			pows[0] += pn;
		} else if(m[3] != "" && m[2] == "") {
			pows[pfn - 1] += pfn;
			if(m[1] == "-")
				pows[pfn - 1] *= -1;
		} else if(m[3] != "" && m[2] != "") {
			pows[pfn - 1] += pn * pfn;
		}

		polynomial = m.suffix().str();
	}
	// for(auto pow: pows)
		// std::cout << pow.first << " - " << pow.second << std::endl;
	for(auto pow = pows.rbegin(); pow != pows.rend(); pow++)
		std::cout << pow->first << " - " << pow->second << std::endl;
	std::cout << std::endl;

	std::stringstream  res;
	for(auto pow = pows.rbegin(); pow != pows.rend(); pow++) {
		if(pow->second > 0 && pow != pows.rbegin())
			res << "+";
		if(pow->second != 0)
			 res << pow->second;
		if(pow->first == 1) {
			if(pow->second != 0)
				res << "*";
			res << "x";
		} else if(pow->first != 0) {
			if(pow->second != 0)
				res << "*";
			res << "x^" << pow->first;
		}
	}

	std::cout << std::endl;
	return (std::string)res.str();
}

int main () {
	std::cout << derivative("-x^2-x^3") << std::endl;
	
	return 0;
}
