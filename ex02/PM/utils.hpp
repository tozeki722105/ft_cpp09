#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>
#include <iostream>

namespace utl
{

/// @brief endより先は返さないstd::next
template <typename Iterator>
Iterator next(const Iterator &it, size_t n, const Iterator &end)
{
	Iterator res = it;
	for (size_t i = 0; i < n && res != end; i++)
		res++;
	return res;
}

/// @brief std::nextを真似たもの
template <typename Iterator>
Iterator next(const Iterator &it, size_t n = 1)
{
	Iterator res = it;
	std::advance(res, n);
	return res;
}

/// @brief std::prevを真似たもの
template <typename Iterator>
Iterator prev(const Iterator &it)
{
	Iterator res = it;
	std::advance(res, -1);
	return res;
}

template <typename Iterator>
void disp(const Iterator &begin, const Iterator &end)
{
	Iterator it = begin;
	while (it != end) {
		std::cout << *it << ' ';  //<< '\n'
		it++;
	}
	std::cout << "\n";
}

template <typename Iterator>
bool isOrder(const Iterator &begin, const Iterator &end)
{
	if (std::distance(begin, end) < 2)
		return true;

	Iterator it = begin;
	for (Iterator next = utl::next(it); next != end; next++) {
		if (*next < *it)
			return false;
		it = next;
	}
	return true;
}

}  // namespace utl

#endif