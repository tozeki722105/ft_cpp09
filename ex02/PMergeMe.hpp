#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "VNode.hpp"
#include "LNode.hpp"
#include "utils.hpp"

#include <ctime>
#include <sys/time.h>

class PMergeMe
{
	typedef std::list<LNode> List;
	typedef std::vector<VNode> Vector;
	typedef std::iterator_traits<List::iterator>::difference_type distance_t;
	typedef long long PMMTime_t;

public:
	PMergeMe(int argc, char **argv);
	~PMergeMe();
	PMergeMe(const PMergeMe &other);
	const PMergeMe &operator=(const PMergeMe &other);

	void exec();

private:
	size_t _elemCount;
	std::vector<int> _arg;
	Vector _vec;
	List _list;

	void binaryInsert(
			Vector &vec, const Vector::iterator &begin, const Vector::iterator &end, VNode &val);
	void mis(Vector &mainChain);

	void binaryInsert(
			List &vec, const List::iterator &begin, const List::iterator &end, LNode &val);
	void mis(List &mainChain);

	void test();
	size_t groupSize(size_t groupIndex);
	inline void getTime(timeval &val)
	{
		gettimeofday(&val, NULL);
	}
	inline PMMTime_t diffTime(timeval start, timeval end)
	{
		return (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	}
};

PMergeMe::PMergeMe(int argc, char **argv)
{
	if (argc <= 1)
		throw std::logic_error("Error");

	_elemCount = static_cast<size_t>(argc - 1);
	_arg.reserve(_elemCount);

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
	_elemCount = other._elemCount;
	_arg = other._arg;
	_vec = other._vec;
	_list = other._list;
	return *this;
}

void PMergeMe::exec()
{
	LNode lnode(0);  // cmpCountのために実体化
	VNode vnode(0);  // cmpCountのために実体化

	std::cout << "Before\t:   ";
	utl::disp(_arg.begin(), _arg.end());

	timeval start, end;
	{
		getTime(start);
		for (size_t i = 0; i < _arg.size(); i++) {
			_vec.push_back(VNode(_arg[i]));
		}
		mis(_vec);
		getTime(end);
	}
	size_t vecCmpCount = vnode.resetCompCount();
	PMMTime_t vecDiff = diffTime(start, end);
	// {
	// 	getTime(start);
	// 	for (size_t i = 0; i < _arg.size(); i++) {
	// 		_list.push_back(LNode(_arg[i]));
	// 	}
	// 	mis(_list);
	// 	getTime(end);
	// }
	size_t listCmpCount = lnode.resetCompCount();
	// PMMTime_t lstDiff = diffTime(start, end);

	// if (!(utl::isOrder(_vec.begin(), _vec.end())) || !(utl::isOrder(_list.begin(), _list.end())))
	// 	throw std::logic_error("Not order");
	// std::cout << "After\t:   ";
	// utl::disp(_vec.begin(), _vec.end());

	// std::cout << "Time to process a range of " << _elemCount
	// 		  << " elements with std::list   : " << lstDiff << " us\n";
	std::cout << "Time to process a range of " << _elemCount
			  << " elements with std::vector : " << vecDiff << " us\n";
	std::cout << "CmpCount : vector = " << vecCmpCount << " list = " << listCmpCount << "\n";
}

#include "MISLst.tpp"
#include "MISVec.tpp"
#include "MISUtils.tpp"

#endif