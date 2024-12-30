#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <sys/time.h>

#include <sstream>
#include <algorithm>

#include "LNode.hpp"
#include "VNode.hpp"
#include "utils.hpp"

template <typename T>
class PMergeMe
{
	typedef typename std::list<VNode<T> > LContainer;
	typedef typename std::vector<VNode<T> > VContainer;

public:
	PMergeMe();
	~PMergeMe();

	void exec();

private:
	std::vector<unsigned int> _arg;
	VContainer _vec;
	LContainer _list;

	void lst_insert(LContainer &vec, const typename LContainer::iterator &begin,
			const typename LContainer::iterator &end, VNode<T> val);
	void lst_mis(LContainer &mainChain);

	void vec_binaryInsert(VContainer &vec, const typename VContainer::iterator &begin,
			const typename VContainer::iterator &end, VNode<T> val);
	void vec_mis(VContainer &mainChain);
};

template <typename T>
PMergeMe<T>::PMergeMe()
{
	// _arg.reserve(argc);
	// std::stringstream ss;
	// unsigned int val;
	// for (size_t i = 1; i < argc; i++) {
	// 	if (argv[i][0] == '\0')
	// 		throw std::runtime_error("arg err");
	// 	ss << argv[i];
	// 	if (!(ss >> val) || ss.eof())
	// 		throw std::runtime_error("arg err");
	// 	_arg.push_back(val);
	// }

	// 奇数
	int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 7, 12, 5, 4, 20, 13};
	// 偶数
	// int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 7, 12, 5, 4, 20, 13, 19};
	// 同値入り
	// int arr[] = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 19};
	int size = sizeof(arr) / sizeof(arr[0]);
	for (size_t i = 0; i < size; i++) {
		_arg.push_back(arr[i]);
	}
}

template <typename T>
PMergeMe<T>::~PMergeMe()
{
}

template <typename T>
void PMergeMe<T>::lst_insert(LContainer &con, const typename LContainer::iterator &begin,
		const typename LContainer::iterator &end, VNode<T> val)
{
	typename LContainer::iterator begin_cp = begin;

	size_t half;
	typename LContainer::iterator mid;
	for (size_t len = std::distance(begin, end); len != 0;) {
		half = len / 2;
		mid = begin_cp;
		std::advance(mid, half);
		if (*mid < val) {
			len -= half + 1;
			begin_cp = ++mid;
		} else {
			len = half;
		}
	}
	con.insert(begin_cp, val);
}

template <typename T>
void PMergeMe<T>::lst_mis(LContainer &mainChain)
{
	if (mainChain.size() <= 2) {
		typename LContainer::iterator first = mainChain.begin();
		typename LContainer::iterator last = utl::next(first);
		if (last != mainChain.end() && *last < *first)
			std::iter_swap(first, last);
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);

	for (typename LContainer::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = false;
	typename LContainer::iterator swapEnd =
			(oddFlag) ? utl::prev(mainChain.end()) : mainChain.end();
	for (typename LContainer::iterator it = mainChain.begin(); it != swapEnd; std::advance(it, 2)) {
		typename LContainer::iterator next = utl::next(it);
		((it->_val < next->_val) ? next : it)->_mainChainFlag = true;
	}

	typename LContainer::iterator bound =
			std::stable_partition(mainChain.begin(), mainChain.end(), isMainChain<T>);

	LContainer subchain;
	std::copy(bound, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(bound, mainChain.end());

	typename LContainer::iterator subchain_it = subchain.begin();
	for (typename LContainer::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->_subChainLinks.push_back(&(*subchain_it));
		subchain_it++;
	}
	VNode<T> *remain = (oddFlag) ? &(*subchain_it) : NULL;

	lst_mis(mainChain);

	typename LContainer::iterator it = mainChain.begin();
	mainChain.insert(mainChain.begin(), *(mainChain.begin()->popSubChainLink()));
	it++;

	size_t n = 1;
	while (it != mainChain.end()) {
		typename LContainer::iterator groupEnd =
				utl::next(it, utl::groupSize(n++), mainChain.end());

		// mainChain it groupEnd
		typename LContainer::iterator last = utl::prev(groupEnd);
		size_t insertCount = std::distance(it, groupEnd);
		for (size_t count = 0; count < insertCount;) {
			if (last->_mainChainFlag) {
				lst_insert(mainChain, mainChain.begin(), last, *(last->popSubChainLink()));
				count++;
			}
			last--;  //
		}
		it = groupEnd;  //
	}
	if (remain)
		lst_insert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();

	for (typename LContainer::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = true;
}

template <typename T>
void PMergeMe<T>::vec_binaryInsert(VContainer &vec, const typename VContainer::iterator &begin,
		const typename VContainer::iterator &end, VNode<T> val)
{
	typename VContainer::iterator insert_it = std::lower_bound(begin, end, val);
	vec.insert(insert_it, val);
}

template <typename T>
void PMergeMe<T>::vec_mis(VContainer &mainChain)
{
	if (mainChain.size() <= 2) {
		typename VContainer::iterator first = mainChain.begin();
		typename VContainer::iterator last = first + 1;
		if (last != mainChain.end() && *last < *first)
			std::iter_swap(first, last);
		return;
	}

	bool oddFlag = (mainChain.size() % 2 != 0);

	for (typename VContainer::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = false;
	for (typename VContainer::iterator it = mainChain.begin(); it != mainChain.end() - oddFlag;
			it += 2) {
		typename VContainer::iterator next = it + 1;
		((it->_val < next->_val) ? next : it)->_mainChainFlag = true;
	}

	typename VContainer::iterator bound =
			std::stable_partition(mainChain.begin(), mainChain.end(), isVMainChain<T>);

	VContainer subchain;
	subchain.reserve((mainChain.size() / 2) + oddFlag);
	std::copy(bound, mainChain.end(), std::back_inserter(subchain));
	mainChain.erase(bound, mainChain.end());

	typename VContainer::iterator subchain_it = subchain.begin();
	for (typename VContainer::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
		it->_subChainLinks.push_back(&(*subchain_it));
		subchain_it++;
	}
	VNode<T> *remain = (oddFlag) ? &(*subchain_it) : NULL;

	vec_mis(mainChain);

	mainChain.reserve(mainChain.size() + subchain.size());

	typename VContainer::iterator it = mainChain.begin();
	mainChain.insert(it, *(it->popSubChainLink()));
	it += 2;

	size_t n = 1;
	while (it != mainChain.end()) {
		typename VContainer::iterator groupEnd =
				utl::next(it, utl::groupSize(n++), mainChain.end());

		// mainChain it groupEnd
		typename VContainer::iterator last = groupEnd - 1;
		size_t insertCount = std::distance(it, groupEnd);
		for (size_t count = 0; count < insertCount;) {
			if (last->_mainChainFlag) {
				vec_binaryInsert(mainChain, mainChain.begin(), last, *(last->popSubChainLink()));
				count++;
			} else
				last--;
		}
		it = groupEnd + insertCount;
	}
	if (remain)
		vec_binaryInsert(mainChain, mainChain.begin(), mainChain.end(), *(remain));

	subchain.clear();

	for (typename VContainer::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		it->_mainChainFlag = true;
}

template <typename T>
void PMergeMe<T>::exec()
{
	// struct timeval beforeVecTime;
	// gettimeofday(&beforeVecTime, NULL);
	for (size_t i = 0; i < _arg.size(); i++) {
		_vec.push_back(VNode<T>(_arg[i]));
	}
	// utl::disp(_vec.begin(), _vec.end());
	vec_mis(_vec);
	// utl::disp(_vec.begin(), _vec.end());
	// struct timeval afterVecTime;
	// gettimeofday(&afterVecTime, NULL);

	for (size_t i = 0; i < _arg.size(); i++) {
		_list.push_back(VNode<T>(_arg[i]));
	}
	utl::disp(_list.begin(), _list.end());
	lst_mis(_list);
	utl::disp(_list.begin(), _list.end());
}

#endif