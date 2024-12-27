#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"

// bool comp(Node &a, Node &b)
// {
// 	return a.val() < b.val();
// }

void binaryInsert(std::vector<Node> &vec, Node &node)
{
	std::vector<Node>::iterator it = std::lower_bound(vec.begin(), vec.end(), node);
	vec.insert(it, node);
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
	Node node(arr[i]);
}