#include <cassert>
#include <cmath>
#include <iostream>

size_t getGroupSize(size_t groupIndex)
{
	if (groupIndex == 1 || groupIndex == 2)
		return 2;

	size_t a = 2;
	size_t b = 2;
	for (size_t i = 3; i <= groupIndex; i++) {
		size_t tmp = b;
		b = a * 2 + b;
		a = tmp;
	}
	return b;
}

size_t newGroupSize(size_t groupIndex)
{
	static const size_t lookupTable[] = {0, 2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366, 2730,
			5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050, 1398102, 2796202, 5592406,
			11184810, 22369622, 44739242, 89478486, 178956970, 357913942};
	static size_t size = sizeof(lookupTable) / sizeof(*lookupTable);

	if (groupIndex == 0)
		throw std::invalid_argument("groupIndex is 0");
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

int main()
{
	assert(getGroupSize(1) == 2);
	assert(getGroupSize(2) == 2);
	assert(getGroupSize(3) == 6);
	assert(getGroupSize(4) == 10);
	assert(getGroupSize(5) == 22);
	assert(getGroupSize(6) == 42);
	assert(getGroupSize(7) == 86);
	assert(getGroupSize(8) == 170);
	// 必要に応じてさらにテストケースを追加
	std::cout << "All test cases passed!" << std::endl;
	for (size_t i = 1; i <= 100; i++) {
		if (getGroupSize(i) != newGroupSize(i))
			std::cout << "out:" << i << "\n";
		// std::cout << getGroupSize(i) << ", ";
	}
}