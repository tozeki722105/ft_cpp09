#include <iostream>
#include <iomanip>
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
		if (count % 2 == 0)
			mainChain.push_back(*i);
		else
			subChain.push_back(*i);
		count++;
	}
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

void mergeInsertionSort(std::vector<int> mainChain)
{
	if (mainChain.size() <= 2) {
		if (mainChain.size() == 2 && !isOrderComp(mainChain.begin(), mainChain.rbegin()))
			std::iter_swap(mainChain.begin(), mainChain.rbegin());
		return;
	}
	std::vector<int> newMainChain;
	std::vector<int> subChain;
	splitChain(mainChain, newMainChain, subChain);
	swapChainVal(newMainChain, subChain);
	disp(newMainChain, "newMainChain");
	disp(subChain, "subChain");
	mergeInsertionSort(newMainChain);
	// insertion(newMainChain, subChain);
}

int main()
{
	int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 7};
	int size = sizeof(arr) / sizeof(arr[0]);
	std::vector<int> vec(arr, arr + size);
	mergeInsertionSort(vec);
}