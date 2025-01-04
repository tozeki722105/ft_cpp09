#include "PMergeMe.hpp"

template <typename T>
void PMergeMe<T>::test()
{
	std::cout << "test test test test test test test test test\n";
}

template <typename T>
size_t PMergeMe<T>::groupSize(size_t groupIndex)
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
