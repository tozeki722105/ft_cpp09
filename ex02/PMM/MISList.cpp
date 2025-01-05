#include <algorithm>

#include "PMergeMe.hpp"
#include "utils.hpp"

void PMergeMe::binaryInsert(
		List &con, const List::iterator &begin, const List::iterator &end, LNode &val)
{
	List::iterator begin_cp = begin;

	distance_t half;
	List::iterator mid;
	for (distance_t len = std::distance(begin, end); len != 0;) {
		half = len / 2;
		mid = begin_cp;
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

void PMergeMe::mergeInsertionSort(List &mainChain)
{
	if (mainChain.size() <= 2) {
		List::iterator first = mainChain.begin();
		List::iterator last = utl::next(first);
		if (mainChain.size() == 2 && *last < *first)
			std::iter_swap(first, last);
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);
	List subchain;
	LNode *remain = NULL;

	List::iterator swapEnd = (oddFlag) ? utl::prev(mainChain.end()) : mainChain.end();
	for (List::iterator it = mainChain.begin(); it != swapEnd; std::advance(it, 2)) {
		List::iterator next = utl::next(it);
		((*it < *next) ? it : next)->setMainChainFlag(false);
	}
	if (oddFlag)
		mainChain.back().setMainChainFlag(false);

	List::iterator boundIt = std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain);

	std::copy(boundIt, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(boundIt, mainChain.end());

	List::iterator subchainIt = subchain.begin();
	for (List::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->pushSubChainPtr(&(*subchainIt));
		subchainIt++;
	}
	if (oddFlag)
		remain = &(*subchainIt);

	mergeInsertionSort(mainChain);

	List::iterator it = mainChain.begin();
	mainChain.insert(mainChain.begin(), *(mainChain.begin()->popSubChainPtr()));
	it++;

	size_t n = 1;
	while (it != mainChain.end()) {
		List::iterator groupEnd = utl::next(it, groupSize(n++), mainChain.end());

		// mainChain it groupEnd
		List::iterator last = utl::prev(groupEnd);
		distance_t insertCount = std::distance(it, groupEnd);
		for (distance_t count = 0; count < insertCount;) {
			if (last->getMainChainFlag()) {
				binaryInsert(mainChain, mainChain.begin(), last, *(last->popSubChainPtr()));
				count++;
			}
			last--;  //
		}
		it = groupEnd;  //
	}
	if (remain)
		binaryInsert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();

	for (List::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->setMainChainFlag(true);
}