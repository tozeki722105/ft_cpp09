#include "BitcoinExchange.hpp"

#include <fstream>
#include <iostream>

#include "Date.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::ifstream ifs("./data.csv");
	if (!ifs)
		throw std::runtime_error("could not open file. => ./data.csv");

	std::string buf;
	// 先頭一行を取得、validate
	std::getline(ifs, buf);
	if (buf != "date,exchange_rate")
		throw std::logic_error("bad input => " + buf);

	while (std::getline(ifs, buf)) {
		std::string dateStr, rateStr;
		devideStr(buf, ",", dateStr, rateStr);
		double rate = numeric<double>(rateStr);
		if (rate < 0.0)
			throw std::logic_error("not a positive number.");
		Date date(dateStr);
		if (!_map.insert(std::make_pair(date, rate)).second)  // keyに重複がある
			throw std::logic_error("duplicate input. => " + dateStr);
	}
	if (_map.empty())  // data.csvが空
		throw std::logic_error("no data file => ./data.csv");
	// for (std::map<Date, double>::iterator i = _map.begin(); i != _map.end(); i++) {
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

std::map<Date, double>::iterator BitcoinExchange::findData(const Date &date)
{
	if (date < _map.begin()->first)
		throw std::logic_error("not found matching data. => " + date.toStr());

	std::map<Date, double>::iterator it = _map.lower_bound(date);
	return (date == it->first) ? it
								  : --it;  // 同じ日付でなければ、dateStrよりひとつ前の日付を返す
}

void BitcoinExchange::exec(const std::string &inputFile)
{
	std::ifstream ifs(inputFile.c_str());
	if (!ifs)
		throw std::runtime_error("could not open file. => " + inputFile);

	std::string buf;
	// 先頭一行を取得、validate
	std::getline(ifs, buf);
	if (buf != "date | value")
		throw std::logic_error("bad input => " + buf);

	while (std::getline(ifs, buf)) {
		try {
			std::string dateStr, amountStr;
			devideStr(buf, " | ", dateStr, amountStr);
			double amount = numeric<double>(amountStr);
			if (amount < 0.0)
				throw std::logic_error("not a positive number.");
			if (amount > 1000.0)
				throw std::logic_error("too large a number.");
			Date date(dateStr);
			std::map<Date, double>::iterator it = findData(date);
			std::cout << dateStr << " => " << amountStr << " = " << amount * it->second << "\n";
		} catch (const std::exception &e) {
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
}