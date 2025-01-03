#include "PMergeMe.hpp"

template <typename T>
void PMergeMe<T>::binaryInsert(List &con, const typename List::iterator &begin,
		const typename List::iterator &end, Node<T> &val)
{
	typename List::iterator begin_cp = begin;

	distance_t half;
	typename List::iterator mid;
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

template <typename T>
void PMergeMe<T>::mis(List &mainChain)
{
	if (mainChain.size() <= 2) {
		typename List::iterator first = mainChain.begin();
		typename List::iterator last = utl::next(first);
		if (last != mainChain.end() && *last < *first)
			std::iter_swap(first, last);
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);
	List subchain;
	Node<T> *remain = NULL;

	typename List::iterator swapEnd = (oddFlag) ? utl::prev(mainChain.end()) : mainChain.end();
	for (typename List::iterator it = mainChain.begin(); it != swapEnd; std::advance(it, 2)) {
		typename List::iterator next = utl::next(it);
		((*it < *next) ? it : next)->setMainChainFlag(false);
	}
	if (oddFlag)
		mainChain.back().setMainChainFlag(false);

	typename List::iterator boundIt =
			std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain<T>);

	std::copy(boundIt, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(boundIt, mainChain.end());

	typename List::iterator subchainIt = subchain.begin();
	for (typename List::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->pushSubChainPtr(&(*subchainIt));
		subchainIt++;
	}
	if (oddFlag)
		remain = &(*subchainIt);

	mis(mainChain);

	typename List::iterator it = mainChain.begin();
	mainChain.insert(mainChain.begin(), *(mainChain.begin()->popSubChainPtr()));
	it++;

	size_t n = 1;
	while (it != mainChain.end()) {
		typename List::iterator groupEnd = utl::next(it, groupSize(n++), mainChain.end());

		// mainChain it groupEnd
		typename List::iterator last = utl::prev(groupEnd);
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

	for (typename List::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->setMainChainFlag(true);
}