#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"

void test()
{
	std::cout << "test test test test test test test test test\n";
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

namespace ft
{
std::vector<Node>::iterator next(
		const std::vector<Node>::iterator &it, size_t n, const std::vector<Node>::iterator &end)
{
	std::vector<Node>::iterator res = it;
	for (size_t i = 0; i < n && res != end; i++)
		res++;
	return res;
}

std::vector<Node>::iterator next(const std::vector<Node>::iterator &it, size_t n = 1)
{
	std::vector<Node>::iterator res = it;
	std::advance(res, n);
	return res;
}

std::vector<Node>::iterator prev(const std::vector<Node>::iterator &it)
{
	std::vector<Node>::iterator res = it;
	std::advance(res, -1);
	return res;
}

void binaryInsert(std::vector<Node> &vec, const std::vector<Node>::iterator &begin,
		const std::vector<Node>::iterator &end, Node val)
{
	std::vector<Node>::iterator insert_it = std::lower_bound(begin, end, val);
	vec.insert(insert_it, val);
}

size_t groupSize(size_t groupIndex)
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
}  // namespace ft

void mis(std::vector<Node> &mainChain)
{
	if (mainChain.size() <= 2) {
		std::vector<Node>::iterator first = mainChain.begin();
		std::vector<Node>::iterator last = ft::next(first);
		if (last != mainChain.end() && *last < *first)
			std::iter_swap(first, last);
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);

	for (std::vector<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = false;
	for (std::vector<Node>::iterator it = mainChain.begin(); it != mainChain.end() - oddFlag;
			std::advance(it, 2)) {
		std::vector<Node>::iterator next = ft::next(it);
		if (it->_val < next->_val)
			next->_mainChainFlag = true;
		else
			it->_mainChainFlag = true;
	}

	std::vector<Node>::iterator bound =
			std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain);

	std::vector<Node> subchain;
	subchain.reserve((mainChain.size() / 2) + oddFlag);
	std::copy(bound, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(bound, mainChain.end());

	std::vector<Node>::iterator subchain_it = subchain.begin();
	for (std::vector<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->_subChainLinks.push_back(subchain_it++);
	}
	std::vector<Node>::iterator remain = (oddFlag) ? subchain_it : subchain.end();

	// disp(mainChain.begin(), mainChain.end());
	mis(mainChain);
	// std::cout << "basecase: STOP\n";
	// disp(mainChain.begin(), mainChain.end());

	mainChain.reserve(mainChain.size() + subchain.size());

	std::vector<Node>::iterator it = mainChain.begin();
	mainChain.insert(it, *(it->popSubChainLink()));
	std::advance(it, 2);

	size_t n = 1;
	while (it != mainChain.end()) {
		std::vector<Node>::iterator groupEnd = ft::next(it, ft::groupSize(n++), mainChain.end());

		// mainChain it groupEnd
		std::vector<Node>::iterator last = ft::prev(groupEnd);
		size_t insertCount = std::distance(it, groupEnd);
		for (size_t count = 0; count < insertCount;) {
			if (last->_mainChainFlag) {
				ft::binaryInsert(mainChain, mainChain.begin(), last, *(last->popSubChainLink()));
				count++;
			} else
				last--;
		}
		it = ft::next(groupEnd, insertCount);
	}
	if (remain != subchain.end())
		ft::binaryInsert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();

	for (std::vector<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
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
		// disp(vec.begin(), vec.end());
		mis(vec);
		// disp(vec.begin(), vec.end());
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
	}
}
