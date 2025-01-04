#include "PMergeMe.hpp"

size_t VNode::_cmpCount = 0;  // cmpCountの初期化
size_t LNode::_cmpCount = 0;  // cmpCountの初期化

int main(int argc, char** argv)
{
	try {
		PMergeMe pmm(argc, argv);
		pmm.exec();
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
}
