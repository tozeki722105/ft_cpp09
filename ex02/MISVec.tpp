#include "PMergeMe.hpp"

template <typename T>
void PMergeMe<T>::binaryInsert(Vector &vec, const typename Vector::iterator &begin,
		const typename Vector::iterator &end, Node<T> val)
{
	typename Vector::iterator insert_it = std::lower_bound(begin, end, val);
	vec.insert(insert_it, val);
}

template <typename T>
void PMergeMe<T>::mis(Vector &mainChain)
{
	if (mainChain.size() <= 2) {
		typename Vector::iterator first = mainChain.begin();
		typename Vector::iterator last = first + 1;
		if (last != mainChain.end() && *last < *first)
			std::iter_swap(first, last);
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);

	for (typename Vector::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = false;
	for (typename Vector::iterator it = mainChain.begin(); it != mainChain.end() - oddFlag;
			it += 2) {
		typename Vector::iterator next = it + 1;
		((it->_val < next->_val) ? next : it)->_mainChainFlag = true;
	}

	typename Vector::iterator bound =
			std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain<T>);

	Vector subchain;
	subchain.reserve((mainChain.size() / 2) + oddFlag);
	std::copy(bound, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(bound, mainChain.end());

	typename Vector::iterator subchain_it = subchain.begin();
	for (typename Vector::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->_subChainLinks.push_back(&(*subchain_it));
		subchain_it++;
	}
	Node<T> *remain = (oddFlag) ? &(*subchain_it) : NULL;

	mis(mainChain);

	mainChain.reserve(mainChain.size() + subchain.size());

	typename Vector::iterator it = mainChain.begin();
	mainChain.insert(it, *(it->popSubChainLink()));
	it += 2;

	size_t n = 1;
	while (it != mainChain.end()) {
		typename Vector::iterator groupEnd = utl::next(it, groupSize(n++), mainChain.end());

		// mainChain it groupEnd
		typename Vector::iterator last = groupEnd - 1;
		size_t insertCount = std::distance(it, groupEnd);
		for (size_t count = 0; count < insertCount;) {
			if (last->_mainChainFlag) {
				binaryInsert(mainChain, mainChain.begin(), last, *(last->popSubChainLink()));
				count++;
			} else
				last--;
		}
		it = groupEnd + insertCount;
	}
	if (remain)
		binaryInsert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();

	for (typename Vector::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = true;
}