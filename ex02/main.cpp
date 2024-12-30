#include "PMergeMe.hpp"

int main()
{
	try {
		PMergeMe<unsigned int>* pmm = new PMergeMe<unsigned int>();
		pmm->exec();
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
