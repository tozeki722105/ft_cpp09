#ifndef NODE_HPP
#define NODE_HPP

#include <list>
#include <vector>

template <typename T>
class Node
{
public:
	Node(T val);
	~Node();
	Node(const Node<T> &other);
	const Node<T> &operator=(const Node<T> &other);

	Node<T> *popSubChainLink();
	bool operator<(const Node<T> &rhs) const;

	T _val;
	bool _mainChainFlag;
	// bool _subChainFlag;
	std::vector<Node<T> *> _subChainLinks;

	static size_t _cmpCount;

private:
	Node();
};

template <typename T>
Node<T>::Node(T val) : _val(val), _mainChainFlag(false)
{
}

template <typename T>
Node<T>::~Node(){};

template <typename T>
Node<T>::Node(const Node &other)
{
	*this = other;
}

template <typename T>
const Node<T> &Node<T>::operator=(const Node<T> &other)
{
	if (this == &other)
		return *this;
	_val = other._val;
	_mainChainFlag = other._mainChainFlag;
	_subChainLinks = other._subChainLinks;
	return *this;
}

template <typename T>
bool Node<T>::operator<(const Node<T> &rhs) const
{
	_cmpCount++;
	return _val < rhs._val;
}

template <typename T>
Node<T> *Node<T>::popSubChainLink()
{
	if (_subChainLinks.empty())
		throw std::runtime_error("subChainLinks is empty");

	Node<T> *res = _subChainLinks.back();
	_subChainLinks.pop_back();
	return res;
}

#include <iomanip>

template <typename T>
std::ostream &operator<<(std::ostream &os, const Node<T> &rhs)
{
	// os << "v:" << std::setw(2) << rhs._val << " ";
	// if (!rhs._subChainLinks.empty())
	// 	os << "s:" << std::setw(2) << rhs._subChainLinks.back()->_val;
	// os << " ";
	os << rhs._val;
	return os;
}

template <typename T>
bool isMainChain(Node<T> &node)
{
	return node._mainChainFlag;
	// return !node._subChainFlag;
}

#endif