#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	try {
		if (argc != 2)
			throw std::logic_error("Error");
		RPN rpn;
		rpn.exec(argv[1]);
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
}