#include <iomanip>
#include <iostream>
#include <vector>

struct Test {
	std::vector<int> vec;
	int count;
	int *ptr;
};

void disp(std::vector<int> &vec)
{
	size_t count = 0;
	for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); i++) {
		std::cout << count << ": " << *i << ";\n";
		count++;
	}
	std::cout << '\n';
}

void rec(Test &t)
{
	if (t.count == 1) {
		std::sort(t.vec.begin(), t.vec.end());
		return;
	}
	t.count++;
	t.ptr = &(*(t.vec.begin()));
	rec(t);
	// 参照で受け取ったSTLの値を入れ替えると全てのstack領域のSTLにも反映される
	disp(t.vec);
}

int main()
{
	int arg[] = {9, 2, 21, 15, 20, 3, 7, 1, 6, 11, 17, 4, 19, 16, 10, 13, 18, 5, 12, 22, 8, 14};
	int size = sizeof(arg) / sizeof(*arg);

	Test t;
	t.count = 0;
	for (size_t i = 0; i < size; i++) {
		t.vec.push_back(arg[i]);
	}
	disp(t.vec);
	rec(t);
	return 0;
}