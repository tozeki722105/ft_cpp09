#include <iostream>
#include <vector>

class MyPair
{
public:
	MyPair(int first, int second);
	~MyPair();

private:
	int first;
	int second;
};

MyPair::MyPair(int first, int second) {}

MyPair::~MyPair() {}

void mIs(std::vector<int> vec)
{
	if (vec.size() == 2) {
		swap(vec[0], vec[1]);
		return;
	}
	std::vector<int> large_vec = make_large_vec(vec);
	std::vector<int> small_vec = make_small_vec(vec);
	swap(large_vec, small_vec);
	mIS(large_vec);
	insertion()
}

int main()
{
	std::vector<int> vec = {
			11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 7};
	mIs(vec);
}