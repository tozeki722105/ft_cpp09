typedef typename std::list<LNode<T> > LContainer;

#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"
#include "utils.hpp"

template <typename T>
void lst_insert(const typename LContainer::iterator &begin,
		const typename LContainer::iterator &end, const typename LContainer::iterator &it)
{
	// typename LContainer::iterator insert_it = std::lower_bound(begin, end, *it);
	// std::rotate(insert_it, it, end);

	typename LContainer::iterator begin_cp = begin;

	size_t half;
	typename LContainer::iterator mid;
	for (size_t len = std::distance(begin, end); len != 0;) {
		half = len / 2;
		mid = begin_cp;
		std::advance(mid, half);
		if (*mid < *it) {
			len -= half + 1;
			begin_cp = ++mid;
		} else {
			len = half;
		}
	}
	std::rotate(begin_cp++, it, end);
}

template <typename T>
void lst_mis(typename LContainer::iterator &begin, typename LContainer::iterator &end)
{
	size_t size = std::distance(begin, end);
	bool isOdd = (size % 2 != 0);
	typename LContainer::iterator remain;

	if (size <= 2) {
		typename LContainer::iterator first = begin;
		typename LContainer::iterator last = utl::next(begin);
		if (last != first && first->_val > last->_val)
			std::iter_swap(first, last);
		return;
	}

	for (typename LContainer::iterator it = begin; it != end; it++)
		it->_mainChainFlag = false;
	typename LContainer::iterator swapEnd = (isOdd) ? utl::prev(end) : end;
	for (typename LContainer::iterator it = begin; it != swapEnd; std::advance(it, 2)) {
		typename LContainer::iterator next = utl::next(it);
		((it->_val < next->_val) ? next : it)->_mainChainFlag = true;
	}

	typename LContainer::iterator bound = std::stable_partition(begin, end, isLMainChain<T>);

	typename LContainer::iterator bound_cp = bound;
	for (typename LContainer::iterator it = begin; it != bound; it++) {
		it->_subChainLinks.push_back(bound_cp++);
	}
	remain = (isOdd) ? bound_cp : end;

	// utl::disp(begin, bound);
	lst_mis(begin, bound);
	std::cout << "basecase: STOP\n";
	// utl::disp(begin, bound);

	typename LContainer::iterator it = begin;
	std::rotate(begin, begin->popSubChainLink(), end);
	it++;

	size_t n = 1;
	while (it != end) {
		typename LContainer::iterator groupEnd = utl::next(it, utl::groupSize(n++), end);

		typename LContainer::iterator last = utl::next(groupEnd, -1);
		size_t insertCount = std::distance(it, groupEnd);
		for (size_t count = 0; count < insertCount;) {
			if (last->_mainChainFlag) {
				lst_insert(begin, last, last->popSubChainLink());
				count++;
			}
			last--;  //
		}
		it = groupEnd;  //
	}
	if (remain != end)
		lst_insert(begin, end, remain);

	for (typename LContainer::iterator it = begin; it != end; it++)
		it->_mainChainFlag = true;
}