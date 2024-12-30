#ifndef NODE_HPP
#define NODE_HPP

#include <list>
#include <vector>

template <typename T>
class Node
{
public:
	T _val;
	bool _mainChainFlag;
	// bool _subChainFlag;

	Node();
	Node(T val);
	virtual ~Node();
	Node(const Node<T> &other);
	const Node<T> &operator=(const Node<T> &other);

	bool operator<(const Node<T> &rhs) const;
};

template <typename T>
Node<T>::Node() : _val(0), _mainChainFlag(false)
{
}

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
	return *this;
}

template <typename T>
bool Node<T>::operator<(const Node<T> &rhs) const
{
	// static size_t count = 1;
	// std::cout << "comp: " << count++ << "\n";
	return _val < rhs._val;
}

template <typename T>
bool isMainChain(Node<T> &node)
{
	return node._mainChainFlag;
	// return !node._subChainFlag;
}

#endif