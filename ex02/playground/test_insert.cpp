#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"

void test(std::vector<Node> &vec)
{
	for (std::vector<Node>::iterator it = vec.begin(); it != vec.end(); it++) {
		vec.insert(it, Node(100));
	}
}

int main()
{
	int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 19};
	int size = sizeof(arr) / sizeof(arr[0]);

	std::vector<Node> vec;
	size_t i = 0;
	for (; i + 1 < size; i++) {
		vec.push_back(Node(arr[i]));
	}
	vec.reserve(1000000);
	test(vec);
}