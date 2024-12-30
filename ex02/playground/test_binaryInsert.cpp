#include <algorithm>  // std::equal, std::sort
#include <cassert>    // assert
#include <cstdlib>    // std::rand, std::srand
#include <ctime>      // std::time
#include <iostream>
#include <list>
#include <vector>  // std::vector

#include "utils.hpp"

void binaryInsert(std::list<int> &con, const std::list<int>::iterator &begin,
		const std::list<int>::iterator &end, int val)
{
	std::list<int>::iterator begin_cp = begin;

	for (size_t len = std::distance(begin, end); len != 0;) {
		size_t half = len / 2;
		std::list<int>::iterator mid = begin_cp;
		std::advance(mid, half);
		if (*mid < val) {
			len -= half + 1;
			begin_cp = ++mid;
		} else {
			len = half;
		}
	}
	con.insert(begin_cp, val);
}

void makeList(std::list<int> &list, int array[], int size)
{
	for (size_t i = 0; i < size; i++) {
		list.push_back(array[i]);
	}
}

void test(int array[], int size, int val)
{
	std::list<int> list;
	makeList(list, array, size);
	binaryInsert(list, list.begin(), list.end(), val);
	utl::disp(list.begin(), list.end());
}

int main()
{
	{
		int array[] = {1, 3, 5, 7, 9};
		int size = sizeof(array) / sizeof(array[0]);
		test(array, size, 4);
	}
	{
		int array[] = {1, 3, 5, 7, 9};
		int size = sizeof(array) / sizeof(array[0]);
		test(array, size, 11);
	}
	{
		int array[] = {1, 3, 5, 7, 9};
		int size = sizeof(array) / sizeof(array[0]);
		test(array, size, 0);
	}
	{
		int array[] = {1, 3, 5, 7, 9};
		int size = sizeof(array) / sizeof(array[0]);
		test(array, size, 5);
	}
}
