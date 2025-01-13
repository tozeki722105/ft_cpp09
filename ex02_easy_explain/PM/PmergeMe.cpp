#include "PmergeMe.hpp"

#include <climits>
#include <iostream>
#include <sstream>

#include "utils.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
	if (argc <= 1)
		throw std::logic_error("Error");

	size_t elemCount = static_cast<size_t>(argc - 1);
	_arg.reserve(elemCount);

	std::stringstream ss;
	long val;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '\0')
			throw std::logic_error("Error");
		ss << argv[i];
		if (!(ss >> val) || !ss.eof() || val < 0 || val > INT_MAX)
			throw std::logic_error("Error");
		ss.clear();

		_arg.push_back(static_cast<int>(val));
	}
}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

const PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this == &other)
		return *this;
	_arg = other._arg;
	_list = other._list;
	return *this;
}

void PmergeMe::exec()
{
	Node node(0);  // cmpCountのために実体化

	std::cout << "Before\t:   ";
	utl::disp(_arg.begin(), _arg.end());

	timeval start, end;
	{
		getTime(start);
		for (size_t i = 0; i < _arg.size(); i++) {
			_list.push_back(Node(_arg[i]));
		}
		mergeInsertionSort(_list);
		getTime(end);
	}
	size_t listCmpCount = node.resetCompCount();
	PMTime_t listDiff = diffTime(start, end);

	// 正しくソートされてなければ、エラー
	if (!(utl::isOrder(_list.begin(), _list.end())))
		throw std::logic_error("Not order");
	std::cout << "After\t:   ";
	utl::disp(_list.begin(), _list.end());

	std::cout << "Time to process a range of " << _arg.size()
			  << " elements with std::list   : " << listDiff << " us\n";
	std::cout << "CmpCount : list = " << listCmpCount << "\n";
}