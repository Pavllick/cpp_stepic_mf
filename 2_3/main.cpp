#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>

class SmallAllocator {
private:
	static const unsigned int MEM_SIZE = 1048576;
	char Memory[MEM_SIZE];
	unsigned int mem_begining;
	unsigned int occupied_mem_size;
	std::map<void *, unsigned int> mem_blocs;
	// std::vector<Bloc> blocs;
public:
	SmallAllocator(): mem_begining(0), occupied_mem_size(0) {};
	void *Alloc(unsigned int Size);
	void *ReAlloc(void *Pointer, unsigned int Size);
	void Free(void *Pointer);
};

void *SmallAllocator::Alloc(unsigned int Size) {
	if(Size + occupied_mem_size > MEM_SIZE)
		throw;
	
	mem_begining = occupied_mem_size;
	occupied_mem_size += Size;
	mem_blocs[&Memory[mem_begining]] = Size;

	return (void *)(&Memory[mem_begining]);
}

void *SmallAllocator::ReAlloc(void *Pointer, unsigned int Size) {
	if(Size + occupied_mem_size > MEM_SIZE)
		throw;
	if(!mem_blocs.count((char *)Pointer))
		throw;
	
	mem_begining = occupied_mem_size;
	occupied_mem_size += Size;
	mem_blocs[&Memory[mem_begining]] = Size;

	unsigned int reloc_i = (Size > mem_blocs[(char *)Pointer] ? mem_blocs[(char *)Pointer] : Size);
	memcpy(&Memory[mem_begining], (char *)Pointer, reloc_i);
		
	Free(Pointer);

	return (void *)(&Memory[mem_begining]);
}

void SmallAllocator::Free(void *Pointer) {
	if(!mem_blocs.count((char *)Pointer))
		throw;

	for(auto p = (char *)Pointer; p != (char *)Pointer + mem_blocs[(char *)Pointer]; p++)
		*p = 0;

	mem_blocs.erase((char *)Pointer);
}

int main(int argc, char **argv) {
	SmallAllocator A1;
	int * A1_P1 = (int *) A1.Alloc(sizeof(int));
	A1_P1 = (int *) A1.ReAlloc(A1_P1, 2 * sizeof(int));
	A1.Free(A1_P1);
	SmallAllocator A2;
	int * A2_P1 = (int *) A2.Alloc(10 * sizeof(int));
	for(unsigned int i = 0; i < 10; i++) A2_P1[i] = i;
	for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 1" << std::endl;
	int * A2_P2 = (int *) A2.Alloc(10 * sizeof(int));
	for(unsigned int i = 0; i < 10; i++) A2_P2[i] = -1;
	for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 2" << std::endl;
	for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 3" << std::endl;
	A2_P1 = (int *) A2.ReAlloc(A2_P1, 20 * sizeof(int));
	for(unsigned int i = 10; i < 20; i++) A2_P1[i] = i;
	for(unsigned int i = 0; i < 20; i++) if(A2_P1[i] != i) std::cout << "ERROR 4" << std::endl;
	for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 5" << std::endl;
	A2_P1 = (int *) A2.ReAlloc(A2_P1, 5 * sizeof(int));
	for(unsigned int i = 0; i < 5; i++) if(A2_P1[i] != i) std::cout << "ERROR 6" << std::endl;
	for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 7" << std::endl;
	A2.Free(A2_P1);
	A2.Free(A2_P2);

	return 0;
}
