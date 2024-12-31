#ifndef VNODE_HPP
#define VNODE_HPP

#include <iomanip>
#include <vector>

#include "Node.hpp"

template <typename T>
class VNode : public Node<T>
{
public:
	VNode(T val);
	virtual ~VNode();
	VNode(const VNode<T> &other);
	const VNode<T> &operator=(const VNode<T> &other);

	VNode<T> *popSubChainLink();
	std::vector<VNode<T> *> _subChainLinks;

private:
	VNode();
};

template <typename T>
VNode<T>::VNode(T val) : Node<T>(val)
{
}

template <typename T>
VNode<T>::~VNode()
{
}

template <typename T>
VNode<T>::VNode(const VNode<T> &other)
{
	*this = other;
}

template <typename T>
const VNode<T> &VNode<T>::operator=(const VNode<T> &other)
{
	if (this == &other)
		return *this;
	Node<T>::operator=(other);
	_subChainLinks = other._subChainLinks;
	return *this;
}

template <typename T>
VNode<T> *VNode<T>::popSubChainLink()
{
	if (_subChainLinks.empty())
		throw std::runtime_error("subChainLinks is empty");

	VNode<T> *res = _subChainLinks.back();
	_subChainLinks.pop_back();
	return res;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const VNode<T> &rhs)
{
	os << "v:" << std::setw(2) << rhs._val << " ";
	if (!rhs._subChainLinks.empty())
		os << "s:" << std::setw(2) << rhs._subChainLinks.back()->_val;
	os << " ";
	return os;
}

template <typename T>
bool isVMainChain(VNode<T> &node)
{
	return node._mainChainFlag;
	// return !node._subChainFlag;
}

#endif