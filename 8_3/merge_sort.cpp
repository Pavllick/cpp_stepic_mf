#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

template<typename T>
std::vector<T> sort(const std::vector<T> arr_head, const std::vector<T> arr_tail) {
	std::vector<T> arr;

	int head_it = 0, tail_it = 0;
	while((arr_head.begin() + head_it != arr_head.end()) &&
				(arr_tail.begin() + tail_it != arr_tail.end())) {

		if(arr_head[head_it] < arr_tail[tail_it])
			arr.push_back(arr_head[head_it++]);
		else
			arr.push_back(arr_tail[tail_it++]);
	}

	if(arr_head.begin() + head_it != arr_head.end())
		arr.insert(arr.end(), arr_head.begin() + head_it, arr_head.end());
	else if(arr_tail.begin() + tail_it != arr_tail.end())
		arr.insert(arr.end(), arr_tail.begin() + tail_it, arr_tail.end());

	return arr;
}

template<typename T>
std::vector<T> merge_sort(const std::vector<T> arr) {

	int arr_centr = arr.size() / 2;
	std::vector<T> head(arr.begin(), arr.begin() + arr_centr);
	std::vector<T> tail(arr.begin() + arr_centr, arr.end());
		
	if(head.size() == 1 && tail.size() == 1)
		return sort(head, tail);

	std::vector<T> sorted_head;
	std::vector<T> sorted_tail;
  #pragma omp parallel
	{
    #pragma omp task firstprivate(sorted_head)
		{
			if(head.size() > 1)
				sorted_head = merge_sort(head);
		}
    #pragma omp task firstprivate(sorted_tail)
		{
			if(tail.size() > 1)
				sorted_tail = merge_sort(tail);
		}

    #pragma omp taskwait
	}
	return sort(sorted_head, sorted_tail);
}

int main(int argc, char **argv) {
	std::ifstream ifs;
	std::string line;
	ifs.open("dataset_12656_4.txt");
	getline(ifs,line);
	
	std::istringstream is(line);
	auto it = std::istream_iterator<int>(is);
	auto end = std::istream_iterator<int>();
	std::vector<int> nums = std::vector<int>(it, end);
	
	// std::vector<int> nums{43, 3, 1, 8, 6, 3, 34, 8, 4, 7, 2, 5, 7, 1};
	std::vector<int> res(merge_sort<int>(nums));

	std::ofstream ofs("out.txt");
	for(auto el: res)
		ofs << el << " ";
	ofs << std::endl;

		for(auto el: res)
			std::cout << el << std::endl;

	return 0;
}
