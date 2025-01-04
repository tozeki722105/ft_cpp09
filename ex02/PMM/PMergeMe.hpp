#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include "Node/VNode.hpp"
#include "Node/LNode.hpp"

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

	inline void getTime(timeval &val)
	{
		gettimeofday(&val, NULL);
	}
	inline PMMTime_t diffTime(timeval start, timeval end)
	{
		return (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	}
};

#endif