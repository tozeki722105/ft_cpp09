#include <algorithm>

#include "PmergeMe.hpp"
#include "utils.hpp"

void PmergeMe::binaryInsert(
		Vector &vec, const Vector::iterator &begin, const Vector::iterator &end, VNode &val)
{
	Vector::iterator insert_it = std::lower_bound(begin, end, val);
	vec.insert(insert_it, val);
}

void PmergeMe::mergeInsertionSort(Vector &mainChain)
{
	if (mainChain.size() <= 2) {
		Vector::iterator first = mainChain.begin();
		Vector::iterator last = first + 1;
		if (mainChain.size() == 2 && *last < *first)
			std::iter_swap(first, last);
		// std::cout << "\n";
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);
	Vector subchain;
	VNode *remain = NULL;

	for (Vector::iterator it = mainChain.begin(); it != mainChain.end() - oddFlag; it += 2) {
		Vector::iterator next = it + 1;
		((*it < *next) ? it : next)->setMainChain(false);
	}
	if (oddFlag)
		mainChain.back().setMainChain(false);

	Vector::iterator boundIt =
			std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain);

	subchain.reserve((mainChain.size() / 2) + oddFlag);
	std::copy(boundIt, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(boundIt, mainChain.end());

	Vector::iterator subchainIt = subchain.begin();
	for (Vector::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->pushSubChain(&(*subchainIt));
		subchainIt++;
	}
	if (oddFlag)
		remain = &(*subchainIt);

	// std::cout << "\n";
	mergeInsertionSort(mainChain);
	mainChain.reserve(mainChain.size() + subchain.size());
	// std::cout << "mainChain\n";
	// utl::disp(mainChain.begin(), mainChain.end());
	// std::cout << "subChain\n";
	// utl::disp(subchain.begin(), subchain.end());

	Vector::iterator it = mainChain.begin();
	mainChain.insert(it, *(it->popSubChain()));  // ここでitの挿している要素が更新される
	it += 2;                                     // 次の要素＋挿入した一個分

	size_t n = 1;
	while (it != mainChain.end()) {
		Vector::iterator groupEnd = utl::next(it, groupSize(n++), mainChain.end());

		Vector::iterator last = groupEnd - 1;
		distance_t insertCount = groupEnd - it;
		for (distance_t count = 0; count < insertCount;) {
			if (last->isMainChain()) {
				binaryInsert(mainChain, mainChain.begin(), last, *(last->popSubChain()));
				count++;
			} else
				last--;  // insertするとlastを指しているNodeも更新されるため、insert時は更新しない
		}
		it = groupEnd + insertCount;  // groupEndも更新されるため、insertCountを足して次に移る
	}
	if (remain)
		binaryInsert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();

	for (Vector::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->setMainChain(true);
	}
	// std::cout << "\n";
}