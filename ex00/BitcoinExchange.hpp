#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <sstream>

class BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	const BitcoinExchange &operator=(const BitcoinExchange &other);
	void exec(const std::string &inputFile);

private:
	std::map<std::string, float> _map;
	// static const float MIN_NUM = 0.0;
	// static const float MAX_NUM = 1000.0;

	void devideStr(const std::string &str, const std::string &delim, std::string &devideA,
			std::string &devideB);
	void checkValidDate(const std::string &dateStr);
	std::map<std::string, float>::iterator findData(const std::string &dateStr);

	template <typename T>
	T numeric(const std::string &valStr);
};

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