#include <iostream>

class StringPointer {
public:
	std::string *operator->() {
		if(!str)
			str = new std::string("");
		return str;
	}
	operator std::string*() { return str; }
	StringPointer(std::string *Pointer) {
		if(!Pointer)
			str = new std::string("");
		else
			str = new std::string(*Pointer);
	}
	~StringPointer() { if(str) delete str; }

	std::string *str;
};

int main() {
	std::string s1 = "Hello, world!";

StringPointer sp1(&s1);
StringPointer sp2(NULL);

std::cout << sp1->length() << std::endl;
std::cout << *sp1 << std::endl;
std::cout << sp2->length() << std::endl;
std::cout << *sp2 << std::endl;
	
	return 0;
}
