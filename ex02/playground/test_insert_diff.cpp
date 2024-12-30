#include <iomanip>
#include <iostream>
#include <list>
#include <vector>

#include "Node.hpp"

void test(std::list<Node> &con)
{
	for (std::list<Node>::iterator it = con.begin(); it != con.end(); it++) {
		con.insert(it, Node(100));
	}
}

int main()
{
	std::cout << "<list>\n";
	{
		int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 19};
		int size = sizeof(arr) / sizeof(arr[0]);

		std::list<Node> con;
		size_t i = 0;
		for (; i + 1 < size; i++) {
			con.push_back(Node(arr[i]));
		}
		std::list<Node>::iterator begin = con.begin();
		std::cout << *begin << "\n";
		std::cout << *con.begin() << "\n";
		con.insert(con.begin(), Node(100));
		std::cout << *begin << "\n";
		std::cout << *con.begin() << "\n";
	}

	std::cout << "<vector>\n";
	{
		int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 19};
		int size = sizeof(arr) / sizeof(arr[0]);

		std::vector<Node> con;
		size_t i = 0;
		for (; i + 1 < size; i++) {
			con.push_back(Node(arr[i]));
		}
		std::vector<Node>::iterator begin = con.begin();
		std::cout << *begin << "\n";
		con.insert(con.begin(), Node(100));
		std::cout << *begin << "\n";
	}
}