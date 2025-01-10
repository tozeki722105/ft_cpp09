#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <sys/time.h>

#include <ctime>
#include <list>
#include <vector>

#include "Node/LNode.hpp"
#include "Node/VNode.hpp"

class PmergeMe
{
	typedef std::list<LNode> List;
	typedef std::vector<VNode> Vector;
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
	Vector _vec;
	List _list;

	// MISVec.cpp
	void binaryInsert(
			Vector &vec, const Vector::iterator &begin, const Vector::iterator &end, VNode &val);
	void mergeInsertionSort(Vector &mainChain);

	// MISList.cpp
	void binaryInsert(
			List &vec, const List::iterator &begin, const List::iterator &end, LNode &val);
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