#include <iostream>
#include <vector>

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int size = sizeof(arr) / sizeof(arr[0]);

	std::vector<int> vec;
	for (size_t i = 0; i < size; i++) {
		vec.push_back(arr[i]);
	}
	std::vector<int>::iterator begin_it = vec.begin();
	std::vector<int>::iterator end_it = vec.end();
	begin_it++;
	end_it--;

	std::vector<int>::reverse_iterator rbegin_it(end_it);
	std::vector<int>::reverse_iterator rend_it(begin_it);
	std::cout << *begin_it << ": " << *end_it << ": " << *rbegin_it << ": " << *rend_it << ";\n";
}