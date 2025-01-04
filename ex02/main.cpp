#include "PMergeMe.hpp"

template <typename T>
size_t Node<T>::_cmpCount = 0;  // cmpCountの初期化

int main(int argc, char** argv)
{
	try {
		PMergeMe<int> pmm(argc, argv);
		pmm.exec();
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
}
