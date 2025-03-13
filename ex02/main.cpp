#include "PM/PmergeMe.hpp"

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
