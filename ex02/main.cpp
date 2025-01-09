#include "PM/PmergeMe.hpp"

size_t Node::_cmpCount = 0;  // cmpCountの初期化

int main(int argc, char** argv)
{
	try {
		PmergeMe pmm(argc, argv);
		pmm.exec();
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
}
