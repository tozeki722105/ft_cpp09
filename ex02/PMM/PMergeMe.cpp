#include "PMergeMe.hpp"

#include <iostream>
#include <sstream>

#include "utils.hpp"

PMergeMe::PMergeMe(int argc, char **argv)
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

PMergeMe::~PMergeMe() {}

PMergeMe::PMergeMe(const PMergeMe &other)
{
	*this = other;
}

const PMergeMe &PMergeMe::operator=(const PMergeMe &other)
{
	if (this == &other)
		return *this;
	_arg = other._arg;
	_vec = other._vec;
	_list = other._list;
	return *this;
}

void PMergeMe::exec()
{
	Node node(0);  // cmpCountのために実体化

	std::cout << "Before\t:   ";
	utl::disp(_arg.begin(), _arg.end());

	timeval start, end;
	{
		getTime(start);
		for (size_t i = 0; i < _arg.size(); i++) {
			_vec.push_back(VNode(_arg[i]));
		}
		mergeInsertionSort(_vec);
		getTime(end);
	}
	size_t vecCmpCount = node.resetCompCount();
	PMMTime_t vecDiff = diffTime(start, end);
	{
		getTime(start);
		for (size_t i = 0; i < _arg.size(); i++) {
			_list.push_back(LNode(_arg[i]));
		}
		mergeInsertionSort(_list);
		getTime(end);
	}
	size_t listCmpCount = node.resetCompCount();
	PMMTime_t listDiff = diffTime(start, end);

	if (!(utl::isOrder(_vec.begin(), _vec.end())) || !(utl::isOrder(_list.begin(), _list.end())))
		throw std::logic_error("Not order");
	std::cout << "After\t:   ";
	utl::disp(_vec.begin(), _vec.end());

	std::cout << "Time to process a range of " << _arg.size()
			  << " elements with std::list   : " << listDiff << " us\n";
	std::cout << "Time to process a range of " << _arg.size()
			  << " elements with std::vector : " << vecDiff << " us\n";
	std::cout << "CmpCount : vector = " << vecCmpCount << "\n";
	std::cout << "CmpCount : list = " << listCmpCount << "\n";
}