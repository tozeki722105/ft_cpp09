#include <string>
#include <sstream>

bool isValidDay(unsigned int year, unsigned int month, unsigned int day)
{
	if (day == 0)
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

void inputDay(const std::string &dateStr)
{
	if (dateStr.empty())
		return;

	std::string str = dateStr;
	// year,month,dayに分ける
	std::string date_vals[3];
	for (size_t i = 0; i < 3; i++) {
		std::string::size_type delimPos = dateStr.find('-');
		date_vals[i] = str.substr(0, delimPos);
		if (i == 2)
			str.erase(0, delimPos);
		else
			str.erase(0, delimPos + sizeof(char));
	}
	if (!str.empty())  // 3つめの'-'があればエラー
		return;

	// 数値に変換する
	std::stringstream ss;
	unsigned int ui;
	// year
	ss << date_vals[0];
	if (!(ss >> ui) || !ss.eof() || ui > 9999)
		return;
	unsigned int _year = ui;
	// month
	ss << date_vals[1];
	if (!(ss >> ui) || !ss.eof() || (ui < 1 || ui > 12))
		return;
	unsigned int _month = ui;
	// day
	ss << date_vals[2];
	if (!(ss >> ui) || !ss.eof() || isValidDay(_year, _month, ui))
		return;
	unsigned int _day = ui;
}