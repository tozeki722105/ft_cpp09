#include <iomanip>
#include <iostream>
#include <vector>

void disp(const std::vector<int> &vec, const std::string &str)
{
	std::cout << str << '\n';
	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << std::setw(3) << vec[i] << ',';
	}
	std::cout << '\n';
}

bool isOrderComp(std::vector<int>::const_iterator i1, std::vector<int>::const_iterator i2)
{
	return *i1 <= *i2;
}

bool isOrderComp(std::vector<int>::const_iterator i1, std::vector<int>::const_reverse_iterator i2)
{
	return *i1 <= *i2;
}

void splitChain(
		const std::vector<int> &src, std::vector<int> &mainChain, std::vector<int> &subChain)
{
	size_t count = 0;
	for (std::vector<int>::const_iterator i = src.begin(); i != src.end(); i++) {
		if (count++ % 2 == 0)
			mainChain.push_back(*i);
		else
			subChain.push_back(*i);
	}
	// 奇数の時、mainのlastをsubに移動
	if (count % 2 != 0) {
		subChain.push_back(mainChain.back());
		mainChain.pop_back();
	}
}

void swapChainVal(std::vector<int> &mainChain, std::vector<int> &subChain)
{
	std::vector<int>::iterator mainIter = mainChain.begin();
	std::vector<int>::iterator subIter = subChain.begin();
	while (mainIter != mainChain.end() && subIter != subChain.end()) {
		if (!isOrderComp(subIter, mainIter))
			std::swap(*mainIter, *subIter);
		mainIter++;
		subIter++;
	}
}

#include "MyPair.hpp"

void makeNewMainChain(std::vector<Chain> &mainChain, std::vector<Chain> &res)
{
	size_t count = 0;
	std::vector<Chain>::iterator i = mainChain.begin();
	while (i != mainChain.end() || i + 1 != mainChain.end()) {
		Chain *subChain = NULL;
		if (mainChain.size() % 2 == 0 ||
				i + 1 != mainChain.end())  // (サイズが奇数 && 次が最後の要素)じゃなければ
			subChain = &(*(i + 1));
		res.push_back(Chain(i->val(), subChain));
		i += 2;
	}
}

void mergeInsertionSort(std::vector<Chain> mainChain)
{
	if (mainChain.size() <= 2) {
		if (mainChain.size() == 2 && !isOrderComp(mainChain.begin(), mainChain.rbegin()))
			std::iter_swap(mainChain.begin(), mainChain.rbegin());
		return;
	}
	std::vector<int> newMainChain;
	std::vector<int> subChain;
	splitChain(mainChain, newMainChain, subChain);
	// ここで再起に渡すstd::vector<Chain> newChain
	swapChainVal(newMainChain, subChain);
	disp(newMainChain, "newMainChain");
	disp(subChain, "subChain");
	mergeInsertionSort(newMainChain);
	// insertion(newMainChain, subChain);
	// mainChain = newMainChain;
}

int main()
{
	int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 7};
	int size = sizeof(arr) / sizeof(arr[0]);
	std::vector<int> vec(arr, arr + size);
	// コンストラクタ時にsubChainがNULLのstd::vector<Chain>を作成
	mergeInsertionSort(vec);
}