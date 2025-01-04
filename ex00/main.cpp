#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	try {
		if (argc < 2)
			throw std::logic_error("could not open file.");

		BitcoinExchange be;
		be.exec(argv[1]);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
}