#include <algorithm>

#include "PmergeMe.hpp"
#include "utils.hpp"

/// @brief 引数が30未満なら,lookupTableから返す
size_t PmergeMe::groupSize(size_t groupIndex)
{
	static const size_t lookupTable[] = {0, 2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366, 2730,
			5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050, 1398102, 2796202, 5592406,
			11184810, 22369622, 44739242, 89478486, 178956970, 357913942};
	static size_t size = sizeof(lookupTable) / sizeof(*lookupTable);

	if (groupIndex == 0)
		throw std::logic_error("groupIndex is 0");
	if (groupIndex < size)
		return lookupTable[groupIndex];

	size_t a = lookupTable[size - 2];
	size_t b = lookupTable[size - 1];
	for (size_t i = size; i <= groupIndex; i++) {
		size_t tmp = b;
		b = a * 2 + b;
		a = tmp;
	}
	return b;
}

void PmergeMe::binaryInsert(
		List &con, const List::iterator &begin, const List::iterator &end, Node &val)
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

void PmergeMe::mergeInsertionSort(List &mainChain)
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
	Node *remain = NULL;

	// 前後のペアを見比べて小さい方のMainChainFlagをfalseに、奇数の余りはfalseにする
	List::iterator swapEnd = (oddFlag) ? utl::prev(mainChain.end()) : mainChain.end();
	for (List::iterator it = mainChain.begin(); it != swapEnd; std::advance(it, 2)) {
		List::iterator next = utl::next(it);
		((*it < *next) ? it : next)->setMainChain(false);
	}
	if (oddFlag)
		mainChain.back().setMainChain(false);

	// MainChainFlagがtrueのNodeを前に移動する
	List::iterator boundIt = std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain);

	// MainChainFlagがfalseのNodeをsubChainにコピーし、mainChainから削除
	std::copy(boundIt, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(boundIt, mainChain.end());

	// mainChainに対応するsubChainのペアのアドレスをpush、奇数の余りはremainで管理する
	List::iterator subchainIt = subchain.begin();
	for (List::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->pushSubChain(&(*subchainIt));
		subchainIt++;
	}
	if (oddFlag)
		remain = &(*subchainIt);

	mergeInsertionSort(mainChain);

	// itは挿入する前の最初の要素を指す
	List::iterator it = mainChain.begin();
	mainChain.insert(mainChain.begin(), *(mainChain.begin()->popSubChain()));
	it++;

	size_t n = 1;  // groupIndex
	while (it != mainChain.end()) {
		List::iterator groupEnd = utl::next(it, groupSize(n++), mainChain.end());

		// groupEndの前をlastとし、insertCountを満たすまで後ろに戻る
		List::iterator last = utl::prev(groupEnd);
		distance_t insertCount = std::distance(it, groupEnd);
		for (distance_t count = 0; count < insertCount;) {
			if (last->isMainChain()) {
				binaryInsert(mainChain, mainChain.begin(), last, *(last->popSubChain()));
				count++;
			}
			last--;  // insertしてもlastを指しているNode変わらないため、loopの度にlastを更新する
		}
		it = groupEnd;  // groupEndも変わらないため、そのまま渡す
	}
	if (remain)
		binaryInsert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();  // subChainを削除

	// mainChainの全てのmainChainFlagをtrueに更新
	for (List::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->setMainChain(true);
}