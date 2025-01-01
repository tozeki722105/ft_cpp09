#include "BitcoinExchange.hpp"

int main()
{
	try {
		BitcoinExchange be;
		be.exec("input.txt");
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}