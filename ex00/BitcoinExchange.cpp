#include "BitcoinExchange.hpp"

#include <fstream>
#include <iostream>

BitcoinExchange::BitcoinExchange()
{
	std::ifstream ifs("./data.csv");
	if (!ifs)
		throw std::runtime_error("could not open file. => ./data.csv");

	std::string buf, dateStr, valStr;
	float rate;

	// 先頭一行を取得、validate
	std::getline(ifs, buf);
	if (buf != "date,exchange_rate")
		throw std::logic_error("bad input => " + buf);

	while (std::getline(ifs, buf)) {
		devideStr(buf, ",", dateStr, valStr);
		rate = numeric<float>(valStr);
		if (rate < 0.0)
			throw std::logic_error("not a positive number.");
		checkValidDate(dateStr);
		if (!_map.insert(std::make_pair(dateStr, rate)).second)  // keyに重複がある
			throw std::logic_error("duplicate input. => " + dateStr);
	}
	if (_map.empty())  // data.csvが空
		throw std::logic_error("no data file => ./data.csv");
	// for (std::map<std::string, float>::iterator i = _map.begin(); i != _map.end(); i++) {
	// 	std::cout << i->first << "; : " << i->second << ';' << std::endl;
	// }
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

const BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this == &other)
		return *this;
	_map = other._map;
	return *this;
}

/// @brief delimを境に文字を抜き出す
void BitcoinExchange::devideStr(const std::string &str, const std::string &delim,
		std::string &devideA, std::string &devideB)
{
	std::string::size_type delimPos = str.find(delim);
	if (delimPos == std::string::npos)
		throw std::logic_error("bad input => " + str);

	devideA = str.substr(0, delimPos);
	devideB = str.substr(delimPos + delim.length());
}

static bool isValidDay(unsigned int year, unsigned int month, unsigned int day)
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

void BitcoinExchange::checkValidDate(const std::string &dateStr)
{
	if (dateStr.empty())
		throw std::logic_error("bad input => " + dateStr);

	unsigned int y, m, d;
	char c1, c2;
	std::stringstream ss(dateStr);
	if (!(ss >> y && ss >> c1 && ss >> m && ss >> c2 && ss >> d && ss.eof() &&
				isValidDay(y, m, d) && c1 == '-' && c2 == '-'))
		throw std::logic_error("bad input => " + dateStr);
}

std::map<std::string, float>::iterator BitcoinExchange::findData(const std::string &dateStr)
{
	if (dateStr < _map.begin()->first)
		throw std::logic_error("not found matching data. => " + dateStr);

	std::map<std::string, float>::iterator it = _map.lower_bound(dateStr);
	return (dateStr == it->first) ? it
								  : --it;  // 同じ日付でなければ、dateStrよりひとつ前の日付を返す
}

void BitcoinExchange::exec(const std::string &inputFile)
{
	std::ifstream ifs(inputFile.c_str());
	if (!ifs)
		throw std::runtime_error("could not open file. => " + inputFile);

	std::string buf, dateStr, valStr;
	float val;
	std::map<std::string, float>::iterator it;

	// 先頭一行を取得、validate
	std::getline(ifs, buf);
	if (buf != "date | value")
		throw std::logic_error("bad input => " + buf);

	while (std::getline(ifs, buf)) {
		try {
			devideStr(buf, " | ", dateStr, valStr);
			val = numeric<float>(valStr);
			if (val < 0.0)
				throw std::logic_error("not a positive number.");
			if (val > 1000.0)
				throw std::logic_error("too large a number.");
			checkValidDate(dateStr);
			it = findData(dateStr);
			std::cout << dateStr << " => " << valStr << " = " << val * it->second << "\n";
		} catch (const std::exception &e) {
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
}