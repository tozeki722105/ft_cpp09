#include <iomanip>
#include <iostream>
#include <vector>

#include "Node.hpp"

void test()
{
	std::cout << "test test test test test test test test test\n";
}

namespace ft
{
std::vector<Node>::iterator next(std::vector<Node>::iterator it, long long n)
{
	std::vector<Node>::iterator res;
	std::advance(res, n);
	return res;
}

}  // namespace ft

void disp(std::vector<Node>::iterator begin, std::vector<Node>::iterator end)
{
	while (begin != end) {
		std::cout << *begin << '\n';
		begin++;
	}
	std::cout << "\n";
}

void binaryInsert(std::vector<Node> &vec, std::vector<Node>::iterator last, Node &val)
{
	std::vector<Node>::iterator insert_it = std::lower_bound(vec.begin(), last, val);
	vec.insert(insert_it, val);
}

std::vector<Node>::iterator mergeSubChain(std::vector<Node> &vec, std::vector<Node>::iterator last)
{
	size_t count = 0;
	while (last != vec.begin()) {
		if (last->_mainChainFlag) {
			std::vector<Node>::iterator insert_it =
					std::lower_bound(vec.begin(), last, *(last->_subChainLinks.back()));
			vec.insert(insert_it, *(last->_subChainLinks.back()));
			count++;
		} else
			last--;
	}
	if (last->_mainChainFlag) {
		std::vector<Node>::iterator insert_it =
				std::lower_bound(vec.begin(), last, *(last->_subChainLinks.back()));
		vec.insert(insert_it, *(last->_subChainLinks.back()));
		count++;
	}
	return ft::next(last, vec.end(), count);
}

void mis(std::vector<Node>::iterator &begin, std::vector<Node>::iterator &end)
{
	size_t size = std::distance(begin, end);
	bool isOdd = (size % 2 != 0);
	std::vector<Node>::iterator remain;

	if (size <= 2) {
		std::vector<Node>::iterator first = begin;
		std::vector<Node>::iterator last = ft::next(begin, 1);
		if (last != first && first->_val > last->_val)
			std::iter_swap(first, last);
		return;
	}

	for (std::vector<Node>::iterator it = begin; it != end - isOdd; std::advance(it, 2)) {
		std::vector<Node>::iterator next = ft::next(it, 1);
		if (it->_val > next->_val)
			it->_mainChainFlag = true;
		else
			next->_mainChainFlag = true;
	}

	std::vector<Node>::iterator bound_it = std::stable_partition(begin, end, isMainChain);

	std::vector<Node>::iterator bound_it_cp = bound_it;
	for (std::vector<Node>::iterator it = begin; it != bound_it; it++) {
		it->_subChainLinks.push_back(bound_it_cp++);
	}
	remain = (isOdd) ? bound_it_cp : end;

	// mis(begin, bound_it);
	std::sort(begin, bound_it);

	// 最初は
	// std::vector<Node>::iterator it =
	// 		mainChain.insert(mainChain.begin(), *(mainChain.begin()->popSubChainLink()));
	// it++;
	// it++;

	size_t group = 1;
	std::vector<Node>::iterator it = begin;
	while (it != end) {
		size_t GroupSize = getGroupSize(group++);
		std::vector<Node>::iterator end_it;
		for (size_t i = 0; i < GroupSize && end_it != end; i++) {
			end_it++;
		}
		it = mergePiars(it, end_it);
		it++;
	}
	// remainがあれば、remainもbinaryInsert
	if (remain != end) {
		Node node = *remain;
		{
			std::vector<Node>::iterator insert_it = std::upper_bound(begin, end, *remain);
			std::copy_backward(insert_it, remain, end);
			*insert_it = node;
		}
	}

	for (std::vector<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->_mainChainFlag = true;
	}

	// イテレータを引数にするなら、endを更新
}

std::vector<Node>::iterator mergePairs(
		std::vector<Node>::iterator &begin, std::vector<Node>::iterator &end)
{
	// std::vector<Node>::reverse_iterator rbegin_it(end);
	// std::vector<Node>::reverse_iterator rend_it(begin);
	std::vector<Node>::iterator last = ft::next(end, -1);

	size_t insertCount = 0;
	while (last != begin) {
		if (last->_mainChainFlag) {
			Node node = *(ft::next(last->_subChainLinks.back(), insertCount));
			last->_subChainLinks.pop_back();
			{
				std::vector<Node>::iterator insert_it = std::upper_bound(begin, last, node);
				std::copy_backward(insert_it, last, end);
				*insert_it = node;
			}
			insertCount++;
		} else
			last--;
	}
	if (last->_mainChainFlag)
}

std::vector<Node>::iterator mergeSubChain(std::vector<Node> &vec, std::vector<Node>::iterator last)
{
	size_t count = 0;
	while (last != vec.begin()) {
		if (last->_mainChainFlag) {
			std::vector<Node>::iterator insert_it =
					std::lower_bound(vec.begin(), last, *(last->_subChainLinks.back()));
			vec.insert(insert_it, *(last->_subChainLinks.back()));
			count++;
		} else
			last--;
	}
	if (last->_mainChainFlag) {
		std::vector<Node>::iterator insert_it =
				std::lower_bound(vec.begin(), last, *(last->_subChainLinks.back()));
		vec.insert(insert_it, *(last->_subChainLinks.back()));
		count++;
	}
	return ft::next(last, vec.end(), count);
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