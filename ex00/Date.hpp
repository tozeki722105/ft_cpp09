#ifndef DATE_HPP
#define DATE_HPP

#include <sstream>
#include <stdexcept>
#include <string>

class Date
{
public:
	Date(std::string dateStr);
	~Date() {};
	Date(const Date &other);
	const Date &operator=(const Date &other);

	const std::string toStr() const;

	bool operator<(const Date &rhs) const;
	bool operator>(const Date &rhs) const;
	bool operator==(const Date &rhs) const;

private:
	Date();
	unsigned int _year;
	unsigned int _month;
	unsigned int _day;
	std::string _str;

	bool isValidDay(unsigned int year, unsigned int month, unsigned int day);
};

#endif
