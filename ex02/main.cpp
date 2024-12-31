#include "PMergeMe.hpp"

int main(int argc, char** argv)
{
	try {
		PMergeMe<unsigned int>* pmm = new PMergeMe<unsigned int>(argc, argv);
		pmm->exec();
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
