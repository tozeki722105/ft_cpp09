#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <sys/time.h>

#include <ctime>
#include <list>
#include <vector>

#include "Node.hpp"

class PmergeMe
{
	typedef std::list<Node> List;
	typedef std::iterator_traits<List::iterator>::difference_type distance_t;
	typedef long long PMTime_t;

public:
	PmergeMe(int argc, char **argv);
	~PmergeMe();
	PmergeMe(const PmergeMe &other);
	const PmergeMe &operator=(const PmergeMe &other);

	void exec();

private:
	std::vector<int> _arg;
	List _list;

	// MISList.cpp
	void binaryInsert(List &vec, const List::iterator &begin, const List::iterator &end, Node &val);
	void mergeInsertionSort(List &mainChain);

	// MIUtils.cpp
	void test();
	size_t groupSize(size_t groupIndex);

	inline void getTime(timeval &val) { gettimeofday(&val, NULL); }
	inline PMTime_t diffTime(timeval start, timeval end)
	{
		return (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	}
};

#endif