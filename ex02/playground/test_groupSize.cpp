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
}