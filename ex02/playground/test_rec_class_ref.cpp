#include <iomanip>
#include <iostream>
#include <vector>

int num[] = {10, 20, 30};

struct Test {
	int *ptr;
	int count;
};

void rec(Test &t)
{
	if (t.count == 2) {
		return;
	}
	t.count++;
	t.ptr = &num[t.count];
	rec(t);
	// 参照で受け取った引数は再起の全てのstackで同じ値を持つ
	std::cout << *t.ptr << std::endl;
}

int main()
{
	Test t;
	t.count = 0;
	t.ptr = &num[t.count];
	rec(t);
	return 0;
}