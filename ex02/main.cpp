#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"
#include "utils.hpp"

void test()
{
	std::cout << "test test test test test test test test test\n";
}

namespace vec
{
void binaryInsert(std::vector<Node> &vec, const std::vector<Node>::iterator &begin,
		const std::vector<Node>::iterator &end, Node val)
{
	std::vector<Node>::iterator insert_it = std::lower_bound(begin, end, val);
	vec.insert(insert_it, val);
}

void mis(std::vector<Node> &mainChain)
{
	if (mainChain.size() <= 2) {
		std::vector<Node>::iterator first = mainChain.begin();
		std::vector<Node>::iterator last = first + 1;
		if (last != mainChain.end() && *last < *first)
			std::iter_swap(first, last);
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);

	for (std::vector<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = false;
	for (std::vector<Node>::iterator it = mainChain.begin(); it != mainChain.end() - oddFlag;
			it += 2) {
		std::vector<Node>::iterator next = it + 1;
		((it->_val < next->_val) ? next : it)->_mainChainFlag = true;
	}

	std::vector<Node>::iterator bound =
			std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain);

	std::vector<Node> subchain;
	subchain.reserve((mainChain.size() / 2) + oddFlag);
	std::copy(bound, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(bound, mainChain.end());

	std::vector<Node>::iterator subchain_it = subchain.begin();
	for (std::vector<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->_subChainLinks.push_back(&(*subchain_it));
		subchain_it++;
	}
	Node *remain = (oddFlag) ? &(*subchain_it) : NULL;

	mis(mainChain);

	mainChain.reserve(mainChain.size() + subchain.size());

	std::vector<Node>::iterator it = mainChain.begin();
	mainChain.insert(it, *(it->popSubChainLink()));
	it += 2;

	size_t n = 1;
	while (it != mainChain.end()) {
		std::vector<Node>::iterator groupEnd = utl::next(it, utl::groupSize(n++), mainChain.end());

		// mainChain it groupEnd
		std::vector<Node>::iterator last = groupEnd - 1;
		size_t insertCount = std::distance(it, groupEnd);
		for (size_t count = 0; count < insertCount;) {
			if (last->_mainChainFlag) {
				vec::binaryInsert(mainChain, mainChain.begin(), last, *(last->popSubChainLink()));
				count++;
			} else
				last--;
		}
		it = groupEnd + insertCount;
	}
	if (remain)
		vec::binaryInsert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();

	for (std::vector<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = true;
}
}  // namespace vec

namespace lst
{
void binaryInsert(std::list<Node> &con, const std::list<Node>::iterator &begin,
		const std::list<Node>::iterator &end, Node &val)
{
	std::list<Node>::iterator insert_it = std::lower_bound(begin, end, val);
	con.insert(insert_it, val);
	// std::list<Node>::iterator begin_cp = begin;

	// size_t half;
	// std::list<Node>::iterator mid;
	// for (size_t len = std::distance(begin, end); len != 0;) {
	// 	half = len / 2;
	// 	mid = utl::next(begin_cp, half);
	// 	if (*mid < val) {
	// 		len -= half + 1;
	// 		begin_cp = ++mid;
	// 	} else
	// 		len = half;
	// }
	// con.insert(begin_cp, val);
}

// void mis(std::list<Node>::iterator begin, std::list<Node>::iterator end)
void mis(std::list<Node> &mainChain)
{
	if (mainChain.size() <= 2) {
		std::list<Node>::iterator first = mainChain.begin();
		std::list<Node>::iterator last = utl::next(first);
		if (last != mainChain.end() && *last < *first)
			std::iter_swap(first, last);
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);

	for (std::list<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = false;
	std::list<Node>::iterator swapEnd = (oddFlag) ? utl::prev(mainChain.end()) : mainChain.end();
	for (std::list<Node>::iterator it = mainChain.begin(); it != swapEnd; std::advance(it, 2)) {
		std::list<Node>::iterator next = utl::next(it);
		((it->_val < next->_val) ? next : it)->_mainChainFlag = true;
	}

	std::list<Node>::iterator bound =
			std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain);

	std::list<Node> subchain;
	std::copy(bound, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(bound, mainChain.end());

	std::list<Node>::iterator subchain_it = subchain.begin();
	for (std::list<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->_subChainLinks.push_back(&(*subchain_it));
		subchain_it++;
	}
	Node *remain = (oddFlag) ? &(*subchain_it) : NULL;

	mis(mainChain);

	std::list<Node>::iterator it = mainChain.begin();
	mainChain.insert(mainChain.begin(), *(mainChain.begin()->popSubChainLink()));
	it++;

	size_t n = 1;
	while (it != mainChain.end()) {
		std::list<Node>::iterator groupEnd = utl::next(it, utl::groupSize(n++), mainChain.end());

		// mainChain it groupEnd
		std::list<Node>::iterator last = utl::prev(groupEnd);
		size_t insertCount = std::distance(it, groupEnd);
		for (size_t count = 0; count < insertCount;) {
			if (last->_mainChainFlag) {
				lst::binaryInsert(mainChain, mainChain.begin(), last, *(last->popSubChainLink()));
				count++;
			}
			last--;  //
		}
		it = groupEnd;  //
	}
	if (remain)
		lst::binaryInsert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();

	for (std::list<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = true;
	// size_t size = std::distance(begin, end);
	// bool isOdd = (size % 2 != 0);
	// Node *remain;

	// if (size <= 2) {
	// 	std::list<Node>::iterator first = begin;
	// 	std::list<Node>::iterator last = utl::next(begin);
	// 	if (last != first && first->_val > last->_val)
	// 		std::iter_swap(first, last);
	// 	return;
	// }

	// for (std::list<Node>::iterator it = begin; it != end; it++)
	// 	it->_mainChainFlag = false;
	// std::list<Node>::iterator swapEnd = (isOdd) ? utl::prev(end) : end;
	// for (std::list<Node>::iterator it = begin; it != swapEnd; std::advance(it, 2)) {
	// 	std::list<Node>::iterator next = utl::next(it);
	// 	((it->_val < next->_val) ? next : it)->_mainChainFlag = true;
	// }

	// std::list<Node>::iterator bound = std::stable_partition(begin, end, isMainChain);

	// std::list<Node>::iterator bound_cp = bound;
	// for (std::list<Node>::iterator it = begin; it != bound; it++) {
	// 	it->_subChainLinks.push_back(&(*bound_cp));
	// 	bound_cp++;
	// }
	// remain = (isOdd) ? &(*bound_cp) : NULL;

	// // ft::disp(begin, end);
	// mis(begin, bound);
	// std::cout << "basecase: STOP\n";
	// utl::disp(begin, end);

	// std::list<Node>::iterator it = begin;

	// ft::insert(begin, bound++, end, ft::next(it->popSubChainLink(), offset++));
	// std::advance(it, 2);

	// size_t n = 1;
	// while (it != end) {
	// 	std::list<Node>::iterator groupEnd = utl::next(it, ft::getGroupSize(n++), end);

	// 	std::list<Node>::iterator last = utl::next(groupEnd, -1);
	// 	size_t insertCount = std::distance(it, groupEnd);
	// 	for (size_t count = 0; count < insertCount;) {
	// 		if (last->_mainChainFlag) {
	// 			ft::insert(begin, bound++, end, ft::next(last->popSubChainLink(), offset++));
	// 			count++;
	// 		} else
	// 			last--;
	// 	}
	// 	it = utl::next(groupEnd, insertCount);
	// }
	// if (!remain)
	// 	ft::insert(begin, bound++, end, remain);

	// for (std::list<Node>::iterator it = begin; it != end; it++)
	// 	it->_mainChainFlag = true;
}
}  // namespace lst

int main()
{
	// 奇数
	// int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 7, 12, 5, 4, 20, 13};
	// 偶数
	// int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 7, 12, 5, 4, 20, 13, 19};
	// 同値入り
	int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 19};
	int size = sizeof(arr) / sizeof(arr[0]);

	std::list<Node> con;
	for (size_t i = 0; i < size; i++) {
		con.push_back(Node(arr[i]));
	}
	try {
		utl::disp(con.begin(), con.end());
		lst::mis(con);
		utl::disp(con.begin(), con.end());
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
	}
}
