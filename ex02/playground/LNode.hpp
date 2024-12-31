#ifndef LNODE_HPP
#define LNODE_HPP

#include <iomanip>
#include <list>
#include <vector>

#include "Node.hpp"

template <typename T>
class LNode : public Node<T>
{
public:
	LNode(T val);
	virtual ~LNode();
	LNode(const LNode<T> &other);
	const LNode<T> &operator=(const LNode<T> &other);

	typename std::list<LNode<T> >::iterator popSubChainLink();
	std::vector<typename std::list<LNode<T> >::iterator> _subChainLinks;

private:
	LNode();
};

template <typename T>
LNode<T>::LNode(T val) : Node<T>(val)
{
}

template <typename T>
LNode<T>::~LNode()
{
}

template <typename T>
LNode<T>::LNode(const LNode<T> &other)
{
	*this = other;
}

template <typename T>
const LNode<T> &LNode<T>::operator=(const LNode<T> &other)
{
	if (this == &other)
		return *this;
	Node<T>::operator=(other);
	_subChainLinks = other._subChainLinks;
	return *this;
}

template <typename T>
typename std::list<LNode<T> >::iterator LNode<T>::popSubChainLink()
{
	if (_subChainLinks.empty())
		throw std::runtime_error("subChainLinks is empty");

	typename std::list<LNode<T> >::iterator res = _subChainLinks.back();
	// _subChainLinks.pop_back();
	return res;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const LNode<T> &rhs)
{
	os << "v:" << std::setw(2) << rhs._val << " ";
	if (!rhs._subChainLinks.empty())
		os << "s:" << std::setw(2) << rhs._subChainLinks.back()->_val;
	os << " ";
	return os;
}

template <typename T>
bool isLMainChain(LNode<T> &node)
{
	return node._mainChainFlag;
	// return !node._subChainFlag;
}

#endif