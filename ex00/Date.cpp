#include "Date.hpp"

Date::Date(std::string dateStr)
{
	if (dateStr.empty())
		throw std::logic_error("bad input => " + dateStr);

	unsigned int y, m, d;
	char c1, c2;
	std::stringstream ss(dateStr);
	if (!(ss >> y && ss >> c1 && ss >> m && ss >> c2 && ss >> d && ss.eof() &&
				isValidDay(y, m, d) && c1 == '-' && c2 == '-'))
		throw std::logic_error("bad input => " + dateStr);
	_year = y;
	_month = m;
	_day = d;
	_str = dateStr;
}

Date::Date(const Date &other)
{
	*this = other;
}

const Date &Date::operator=(const Date &other)
{
	if (this == &other)
		return *this;
	_year = other._year;
	_month = other._month;
	_day = other._day;
	_str = other._str;
	return *this;
}

bool Date::isValidDay(unsigned int year, unsigned int month, unsigned int day)
{
	if (!(year >= 1 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31))
		return false;

	if (month == 2) {
		if ((year % 4 == 0 && year % 100 == 0 && year % 400 == 0) ||
				(year % 4 == 0 && year % 100 != 0))  // 閏年なら
			return day <= 29;
		else
			return day <= 28;
	} else if (month == 4 || month == 6 || month == 9 || month == 11)
		return day <= 30;
	else
		return day <= 31;
}

const std::string &Date::toStr() const
{
	return _str;
}

bool Date::operator<(const Date &rhs) const
{
	return (_year < rhs._year) || (_year == rhs._year && _month < rhs._month) ||
		   (_year == rhs._year && _month == rhs._month && _day < rhs._day);
}

bool Date::operator>(const Date &rhs) const
{
	return rhs < *this;
}

bool Date::operator==(const Date &rhs) const
{
	return !(*this < rhs) && !(rhs < *this);
}
