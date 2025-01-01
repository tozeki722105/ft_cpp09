#include <sstream>
#include <string>
#include <iostream>

bool isValidDay(unsigned int year, unsigned int month, unsigned int day)
{
	if (!(year >= 1 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31))
		return false;

	if (month == 2) {
		if ((year % 4 == 0 && year % 100 == 0 && year % 400 == 0) ||
				(year % 4 == 0 && year % 100 != 0))  // 閏年なら
			return day <= 29;
		else
			return day <= 28;
	} else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return day <= 30;
	} else {
		return day <= 31;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	std::string str = argv[1];
	// std::string str = "2009-01-11";

	unsigned int y, m, d;
	char c1, c2;
	std::stringstream ss(str);
	if (!(ss >> y && ss >> c1 && ss >> m && ss >> c2 && ss >> d && ss.eof() &&
				isValidDay(y, m, d) && c1 == '-' && c2 == '-')) {
		std::cout << "ko\n";
		return 1;
	}
	std::cout << "ok: " << y << c1 << m << c2 << d << ";\n";
}