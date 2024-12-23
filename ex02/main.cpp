#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"

void test()
{
	std::cout << "test test test test test test test test test\n";
}

void disp(std::vector<Node>::iterator begin, std::vector<Node>::iterator end)
{
	while (begin != end) {
		std::cout << *begin << '\n';
		begin++;
	}
	std::cout << "\n";
}

void mis(std::vector<Node> &vec)
{
	if (vec.size() <= 2) {
		std::vector<Node>::iterator first = vec.begin();
		std::vector<Node>::iterator last = first + 1;
		if (last != vec.end() && first->val() > last->val())
			std::iter_swap(first, last);
		return;
	}

	// 2要素でペアを作り、ペア間で昇順にする
	bool isOdd = (vec.size() % 2 != 0);
	for (std::vector<Node>::iterator it = vec.begin(); it != vec.end() - isOdd; it += 2) {
		if (it->val() > (it + 1)->val())
			std::iter_swap(it, it + 1);
	}

	// indexを振る
	size_t i = 0;
	for (std::vector<Node>::iterator it = vec.begin(); it != vec.end(); it++) {
		it->_index = i++;
	}

	// 小さいペア・余りを後ろに移動
	std::vector<Node>::iterator ret = std::stable_partition(vec.begin(), vec.end(), isOddIndex);

	// 小さいペア・余りをsubChainにcopy
	std::vector<Node> subchain;
	subchain.reserve((vec.size() / 2) + isOdd);
	std::copy(ret, vec.end(), std::back_inserter(subchain));

	// 小さいペア・余りをmainChainから削除 (end()は勝手に更新)
	vec.erase(ret, vec.end());

	// 小さいペアへのリンクをmainChainの_subChainLinksにpush
	// 余りは別のイテレータで管理
	std::vector<Node>::iterator subchain_it = subchain.begin();
	for (std::vector<Node>::iterator it = vec.begin(); it != vec.end(); it++) {
		it->_subChainLinks.push_back(subchain_it++);
	}
	std::vector<Node>::iterator remain = subchain.end();
	if (isOdd)
		remain = subchain_it;

	mis(vec);

	// insertion
	vec.reserve(vec.size() + subchain.size());
	std::vector<Node>::iterator it = vec.begin();
	vec.insert(vec.begin(), *(it->popSubChainLink()));
	it++;
	size_t n = 1;
	while (it != vec.end()) {
		size_t size = getGroupSize(n++);
		std::vector<Node>::iterator last = it;
		for (size_t i = 0; i < size && last != vec.end(); i++)
			last++;
		for (size_t i = last; i < count; i++) {
			binaryInsert(i, *(it->popSubChainLink()));
		}
		it = last + 1;
	}
	// remainがあれば、remainもbinaryInsert
	// subChain.clear();
	// イテレータを引数にするなら、endを更新
}

int main()
{
	int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13};  //, 19
	int size = sizeof(arr) / sizeof(arr[0]);

	std::vector<Node> vec;
	for (size_t i = 0; i < size; i++) {
		vec.push_back(Node(arr[i]));
	}
	mis(vec);
}

// void binarySort(std::vector<Chain> vec, Chain &chain)
// {
// 	std::vector<Chain>::iterator it;
// 	while (1) {
// 		it = vec.begin() + (vec.size() / 2);
// 		// it = 全体サイズの半分
// 		if (it->val() <= chain.val()) {
// 			if ((it + 1)->val() > chain.val())
// 				break;
// 			else
// 				it = (-it) / 2;
// 		} else if () {
// 		}
// 	}
// 	vec.insert(it, chain);
// }