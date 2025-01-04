#include "PMergeMe.hpp"

template <typename T>
void PMergeMe<T>::binaryInsert(Vector &vec, const typename Vector::iterator &begin,
		const typename Vector::iterator &end, Node<T> &val)
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
		if (mainChain.size() == 2 && *last < *first)
			std::iter_swap(first, last);
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);
	Vector subchain;
	Node<T> *remain = NULL;

	for (typename Vector::iterator it = mainChain.begin(); it != mainChain.end() - oddFlag;
			it += 2) {
		typename Vector::iterator next = it + 1;
		((*it < *next) ? it : next)->setMainChainFlag(false);
	}
	if (oddFlag)
		mainChain.back().setMainChainFlag(false);

	typename Vector::iterator boundIt =
			std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain<T>);

	subchain.reserve((mainChain.size() / 2) + oddFlag);
	std::copy(boundIt, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(boundIt, mainChain.end());

	typename Vector::iterator subchainIt = subchain.begin();
	for (typename Vector::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->pushSubChainPtr(&(*subchainIt));
		subchainIt++;
	}
	if (oddFlag)
		remain = &(*subchainIt);

	mis(mainChain);

	mainChain.reserve(mainChain.size() + subchain.size());

	typename Vector::iterator it = mainChain.begin();
	mainChain.insert(it, *(it->popSubChainPtr()));
	it += 2;

	size_t n = 1;
	while (it != mainChain.end()) {
		typename Vector::iterator groupEnd = utl::next(it, groupSize(n++), mainChain.end());

		// mainChain it groupEnd
		typename Vector::iterator last = groupEnd - 1;
		distance_t insertCount = groupEnd - it;
		for (distance_t count = 0; count < insertCount;) {
			if (last->getMainChainFlag()) {
				binaryInsert(mainChain, mainChain.begin(), last, *(last->popSubChainPtr()));
				count++;
			} else
				last--;
		}
		it = groupEnd + insertCount;
	}
	if (remain)
		binaryInsert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();

	for (typename Vector::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->setMainChainFlag(true);
	}
}