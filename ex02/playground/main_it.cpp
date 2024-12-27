#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"

void test()
{
	std::cout << "test test test test test test test test test\n";
}

namespace ft
{
// std::vector<Node>::iterator safetyNext(
// 		const std::vector<Node>::iterator &begin, const std::vector<Node>::iterator &end, size_t n)
// {
// 	std::vector<Node>::iterator res = begin;
// 	for (size_t i = 0; i < n && res != end; i++)
// 		res++;
// 	return res;
// }

std::vector<Node>::iterator next(
		const std::vector<Node>::iterator &it, int n, const std::vector<Node>::iterator &end)
{
	std::vector<Node>::iterator res = it;
	for (size_t i = 0; i < n && res != end; i++)
		res++;
	return res;
}

std::vector<Node>::iterator next(const std::vector<Node>::iterator &it, int n = 1)
{
	std::vector<Node>::iterator res = it;
	std::advance(res, n);
	return res;
}

void disp(const std::vector<Node>::iterator &begin, const std::vector<Node>::iterator &end)
{
	std::vector<Node>::iterator it = begin;
	while (it != end) {
		std::cout << *it;  //<< '\n'
		it++;
	}
	std::cout << "\n";
}

size_t getGroupSize(size_t groupIndex)
{
	if (groupIndex == 1 || groupIndex == 2)
		return 2;

	size_t a = 2;
	size_t b = 2;
	for (size_t i = 3; i <= groupIndex; i++) {
		size_t tmp = b;
		b = a * 2 + b;
		a = tmp;
	}
	return b;
}

void insert(std::vector<Node>::iterator begin, std::vector<Node>::iterator mainEnd,
		std::vector<Node>::iterator subEnd, std::vector<Node>::iterator subChainIt)
{
	if (subChainIt < mainEnd || subChainIt >= subEnd)
		throw std::runtime_error("subChain position error");
	std::vector<Node>::iterator it = std::upper_bound(begin, mainEnd, *subChainIt);
	std::rotate(it, subChainIt, subEnd);
	// ft::next(mainEnd)
}
}  // namespace ft

void mis(const std::vector<Node>::iterator &begin, const std::vector<Node>::iterator &end)
{
	size_t size = std::distance(begin, end);
	bool isOdd = (size % 2 != 0);
	std::vector<Node>::iterator remain;

	if (size <= 2) {
		std::vector<Node>::iterator first = begin;
		std::vector<Node>::iterator last = ft::next(begin);
		if (last != first && first->_val > last->_val)
			std::iter_swap(first, last);
		return;
	}

	for (std::vector<Node>::iterator it = begin; it != end; it++)
		it->_mainChainFlag = false;
	for (std::vector<Node>::iterator it = begin; it != end - isOdd; std::advance(it, 2)) {
		std::vector<Node>::iterator next = ft::next(it);
		((it->_val < next->_val) ? next : it)->_mainChainFlag = true;
	}

	std::vector<Node>::iterator bound = std::stable_partition(begin, end, isMainChain);

	std::vector<Node>::iterator bound_cp = bound;
	for (std::vector<Node>::iterator it = begin; it != bound; it++) {
		it->_subChainLinks.push_back(bound_cp++);
	}
	remain = (isOdd) ? bound_cp : end;

	// ft::disp(begin, end);
	mis(begin, bound);
	std::cout << "basecase: STOP\n";
	ft::disp(begin, end);

	std::vector<Node>::iterator it = begin;
	size_t offset = 0;

	ft::insert(begin, bound++, end, ft::next(it->popSubChainLink(), offset++));
	std::advance(it, 2);

	size_t n = 1;
	while (it != end) {
		std::vector<Node>::iterator groupEnd = ft::next(it, ft::getGroupSize(n++), end);
		std::vector<Node>::iterator last = ft::next(groupEnd, -1);

		size_t insertCount = std::distance(it, groupEnd);
		for (size_t count = 0; count < insertCount;) {
			if (last->_mainChainFlag) {
				ft::insert(begin, bound++, end, ft::next(last->popSubChainLink(), offset++));
				count++;
			} else
				last--;
		}
		it = ft::next(groupEnd, insertCount);
	}
	if (remain != end)
		ft::insert(begin, bound++, end, remain);

	for (std::vector<Node>::iterator it = begin; it != end; it++)
		it->_mainChainFlag = true;
}

int main()
{
	// 奇数
	int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 7, 12, 5, 4, 20, 13};
	// 偶数
	// int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 7, 12, 5, 4, 20, 13, 19};
	// 同値入り
	// int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 19};
	int size = sizeof(arr) / sizeof(arr[0]);

	std::vector<Node> vec;
	for (size_t i = 0; i < size; i++) {
		vec.push_back(Node(arr[i]));
	}
	try {
		// ft::disp(vec.begin(), vec.end());
		mis(vec.begin(), vec.end());
		// ft::disp(vec.begin(), vec.end());
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
	}
}