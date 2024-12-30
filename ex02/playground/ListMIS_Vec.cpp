#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"
#include "utils.hpp"

template <typename T>
void binaryInsert(std::list<Node<T>> &con, const typename std::list<Node<T>>::iterator &begin,
		const typename std::list<Node<T>>::iterator &end, Node<T> &val)
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

template <typename T>
void mis(std::list<Node<T>> &mainChain)
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
}