#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();
	void exec(const std::string &inputFile);

private:
	std::map<std::string, float> _map;
	const float MIN_NUM = 0.0;
	const float MAX_NUM = 1000.0;

	void devideStr(const std::string &str, const std::string &delim, std::string &devideA,
			std::string &devideB);
	void checkValidDate(const std::string &dateStr);
	std::map<std::string, float>::iterator findData(const std::string &dateStr);

	template <typename T>
	T BitcoinExchange::numeric(const std::string &valStr);
};

#include <sstream>
#include <fstream>
#include <iostream>

BitcoinExchange::BitcoinExchange()
{
	std::ifstream ifs("./data.csv");
	if (!ifs)
		throw std::runtime_error("could not open file. => ./data.csv");

	std::string buf, dateStr, valStr;
	float rate;
	while (std::getline(ifs, buf)) {
		devideStr(buf, ",", dateStr, valStr);
		rate = numeric<float>(valStr);
		if (rate < MIN_NUM)
			throw std::logic_error("not a positive number.");
		checkValidDate(dateStr);
		if (!_map.insert(std::make_pair(dateStr, rate)).second)  // keyに重複がある
			throw std::logic_error("duplicate input. => " + dateStr);
	}
	if (_map.empty())
		throw std::logic_error("no data file => ./data.csv");
	// for (std::map<std::string, float>::iterator i = _map.begin(); i != _map.end(); i++) {
	// 	std::cout << i->first << "; : " << i->second << ';' << std::endl;
	// }
}

BitcoinExchange::~BitcoinExchange() {}

/// @brief delimを境に文字を抜き出す
void BitcoinExchange::devideStr(const std::string &str, const std::string &delim,
		std::string &devideA, std::string &devideB)
{
	std::string::size_type delimPos = str.find(delim);
	if (delimPos == std::string::npos)
		throw std::logic_error("no delim input. => " + str);

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

template <typename T>
T BitcoinExchange::numeric(const std::string &valStr)
{
	if (valStr.empty())
		throw std::logic_error("bad input => " + valStr);

	std::stringstream ss(valStr);
	T val;
	if (!(ss >> val) || !ss.eof())
		throw std::logic_error("bad input => " + valStr);
	return val;
}

std::map<std::string, float>::iterator BitcoinExchange::findData(const std::string &dateStr)
{
	if (dateStr < _map.begin()->first)
		throw std::logic_error("not found matching data. => " + dateStr);

	std::map<std::string, float>::iterator it = _map.lower_bound(dateStr);
	if (dateStr != it->first)
		it--;
	return it;
}

void BitcoinExchange::exec(const std::string &inputFile)
{
	std::ifstream ifs(inputFile);
	if (!ifs)
		throw std::runtime_error("could not open file. => " + inputFile);

	std::string buf, dateStr, valStr;
	float val;
	std::map<std::string, float>::iterator it;
	while (std::getline(ifs, buf)) {
		try {
			devideStr(buf, " | ", dateStr, valStr);
			val = numeric<float>(valStr);
			if (val < MIN_NUM)
				throw std::logic_error("not a positive number.");
			if (val > MAX_NUM)
				throw std::logic_error("too large a number.");
			checkValidDate(dateStr);
			it = findData(dateStr);
			std::cout << dateStr << " => " << val << " = " << val * it->second << "\n";
		} catch (const std::exception &e) {
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
}

#endif