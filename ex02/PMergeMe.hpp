#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include "Node.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "utils.hpp"

#include <ctime>
#include <sys/time.h>

template <typename T>
class PMergeMe
{
	typedef typename std::list<Node<T> > List;
	typedef typename std::vector<Node<T> > Vector;
	typedef unsigned long long time_t;

public:
	PMergeMe(int argc, char **argv);
	~PMergeMe();
	PMergeMe(const PMergeMe &other);
	const PMergeMe<T> &operator=(const PMergeMe<T> &other);

	void exec();

private:
	size_t _elemCount;
	std::vector<unsigned int> _arg;
	Vector _vec;
	List _list;

	void binaryInsert(Vector &vec, const typename Vector::iterator &begin,
			const typename Vector::iterator &end, Node<T> val);
	void mis(Vector &mainChain);

	void binaryInsert(List &vec, const typename List::iterator &begin,
			const typename List::iterator &end, Node<T> val);
	void mis(List &mainChain);

	void test();
	size_t groupSize(size_t groupIndex);
	inline void getTime(timeval &val)
	{
		gettimeofday(&val, NULL);
	}
	inline time_t diffTime(timeval start, timeval end)
	{
		return (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	}
};

template <typename T>
PMergeMe<T>::PMergeMe(int argc, char **argv)
{
	if (argc <= 1)
		throw std::runtime_error("Invalid argment count");

	_elemCount = argc - 1;
	_arg.reserve(_elemCount);

	std::stringstream ss;
	unsigned int val;
	for (size_t i = 1; i < argc; i++) {
		if (argv[i][0] == '\0')
			throw std::runtime_error("Invalid argment");
		ss << argv[i];
		if (!(ss >> val) || !ss.eof())
			throw std::runtime_error("Invalid argment");
		ss.clear();

		_arg.push_back(val);
	}
}

template <typename T>
PMergeMe<T>::~PMergeMe()
{
}

template <typename T>
PMergeMe<T>::PMergeMe(const PMergeMe &other)
{
	*this = other;
}

template <typename T>
const PMergeMe<T> &PMergeMe<T>::operator=(const PMergeMe<T> &other)
{
	if (this == &other)
		return *this;
	_elemCount = other._elemCount;
	_arg = other._arg;
	_vec = other._vec;
	_list = other._list;
	return *this;
}

template <typename T>
void PMergeMe<T>::exec()
{
	Node<unsigned int> node(0);  // cmpCountのために実体化

	std::cout << "Before\t:   ";
	utl::disp(_arg.begin(), _arg.end());

	timeval start, end;
	{
		getTime(start);
		for (size_t i = 0; i < _arg.size(); i++) {
			_vec.push_back(Node<T>(_arg[i]));
		}
		mis(_vec);
		getTime(end);
	}
	size_t vecCmpCount = node._cmpCount;
	node._cmpCount = 0;
	time_t vecDiff = diffTime(start, end);
	{
		getTime(start);
		for (size_t i = 0; i < _arg.size(); i++) {
			_list.push_back(Node<T>(_arg[i]));
		}
		mis(_list);
		getTime(end);
	}
	size_t lstCmpCount = node._cmpCount;
	node._cmpCount = 0;
	time_t lstDiff = diffTime(start, end);

	std::cout << "After\t:   ";
	utl::disp(_vec.begin(), _vec.end());

	std::cout << "Time to process a range of " << _elemCount
			  << " elements with std::list   : " << lstDiff << " us\n";
	std::cout << "Time to process a range of " << _elemCount
			  << " elements with std::vector : " << vecDiff << " us\n";
	std::cout << "CmpCount : vector = " << vecCmpCount << " list = " << lstCmpCount << "\n";
}

#include "MISLst.tpp"
#include "MISVec.tpp"
#include "MISUtils.tpp"

#endif