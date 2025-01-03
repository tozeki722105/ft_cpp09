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

	// getter
	T getVal() const;
	bool getMainChainFlag() const;
	Node<T> *popSubChainPtr();
	// setter
	void setMainChainFlag(bool val);
	void pushSubChainPtr(Node<T> *subChainNode);

	size_t resetCompCount();
	bool operator<(const Node<T> &rhs) const;

private:
	Node();

	T _val;
	bool _mainChainFlag;
	std::vector<Node<T> *> _subChainPtrs;

	static size_t _cmpCount;  // 比較をカウントする静的メンバ変数
};

template <typename T>
Node<T>::Node(T val) : _val(val), _mainChainFlag(true)
{
}

template <typename T>
Node<T>::~Node()
{
}

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
	_subChainPtrs = other._subChainPtrs;
	_mainChainFlag = other._mainChainFlag;
	return *this;
}

template <typename T>
T Node<T>::getVal() const
{
	return _val;
}

template <typename T>
bool Node<T>::getMainChainFlag() const
{
	return _mainChainFlag;
}

template <typename T>
Node<T> *Node<T>::popSubChainPtr()
{
	if (_subChainPtrs.empty())
		throw std::runtime_error("subChainPtrs is empty");

	Node<T> *res = _subChainPtrs.back();
	_subChainPtrs.pop_back();
	return res;
}

template <typename T>
void Node<T>::setMainChainFlag(bool val)
{
	_mainChainFlag = val;
}

template <typename T>
void Node<T>::pushSubChainPtr(Node<T> *subChainPtr)
{
	if (!subChainPtr)
		throw std::runtime_error("subChainNode is NULL");

	_subChainPtrs.push_back(subChainPtr);
}

template <typename T>
size_t Node<T>::resetCompCount()
{
	size_t res = _cmpCount;
	_cmpCount = 0;
	return res;
}

template <typename T>
bool Node<T>::operator<(const Node<T> &rhs) const
{
	_cmpCount++;
	return _val < rhs._val;
}

#include <iomanip>

template <typename T>
bool isMainChain(Node<T> &node)
{
	return node.getMainChainFlag();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Node<T> &rhs)
{
	// os << "v:" << std::setw(2) << rhs._val << " ";
	// if (!rhs._subChainPtrs.empty())
	// 	os << "s:" << std::setw(2) << rhs._subChainPtrs.back()->_val;
	// os << " ";
	os << rhs.getVal();
	return os;
}

#endif