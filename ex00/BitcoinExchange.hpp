#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <sstream>
#include <string>
#include "Date.hpp"

class BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	const BitcoinExchange &operator=(const BitcoinExchange &other);
	void exec(const std::string &inputFile);

private:
	std::map<Date, double> _map;

	void devideStr(const std::string &str, const std::string &delim, std::string &devideA,
			std::string &devideB);
	std::map<Date, double>::iterator findData(const Date &date);

	template <typename T>
	T numeric(const std::string &valStr);
};

/// @brief 文字列を数値に変換する
/// @tparam T 数値型
/// @return 正常に変換できれば、数値を返す
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

#endif