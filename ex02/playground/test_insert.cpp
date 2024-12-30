#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"

void test(std::vector<Node> &con)
{
	for (std::vector<Node>::iterator it = con.begin(); it != con.end(); it++) {
		con.insert(it, Node(100));
		// 一番先頭にinsertし続けるため、いつかメモリの再割り当てが起き、イテレータが無効になる
	}
}

int main()
{
	int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 19};
	int size = sizeof(arr) / sizeof(arr[0]);

	std::vector<Node> con;
	size_t i = 0;
	for (; i + 1 < size; i++) {
		con.push_back(Node(arr[i]));
	}
	con.reserve(100);
	test(con);
}