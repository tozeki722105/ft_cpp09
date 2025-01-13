#include "Node.hpp"

#include <iomanip>

Node::Node() : _mainChainFlag(true) {}

Node::Node(int val) : _val(val), _mainChainFlag(true) {}

Node::~Node() {}

Node::Node(const Node &other)
{
	*this = other;
}

const Node &Node::operator=(const Node &other)
{
	if (this == &other)
		return *this;
	_val = other._val;
	_mainChainFlag = other._mainChainFlag;
	_subChains = other._subChains;
	return *this;
}

int Node::getVal() const
{
	return _val;
}

bool Node::isMainChain() const
{
	return _mainChainFlag;
}

void Node::setMainChain(bool val)
{
	_mainChainFlag = val;
}

/// @brief cmpCountを0にし、それまでの値を返す
size_t Node::resetCompCount()
{
	size_t res = _cmpCount;
	_cmpCount = 0;
	return res;
}

bool Node::operator<(const Node &rhs) const
{
	_cmpCount++;
	// std::cout << "i: " << std::setw(2) << _cmpCount << " left: " << std::setw(2) << _val
	// 		  << " right: " << std::setw(2) << rhs._val << "\n";
	return _val < rhs._val;
}

Node *Node::popSubChain()
{
	if (_subChains.empty())
		throw std::logic_error("subChains is empty");

	Node *res = _subChains.back();
	_subChains.pop_back();
	return res;
}

void Node::pushSubChain(Node *subChainPtr)
{
	if (!subChainPtr)
		throw std::logic_error("subChainPtr is NULL");

	_subChains.push_back(subChainPtr);
}

bool isMainChain(Node &node)
{
	return node.isMainChain();
}

std::ostream &operator<<(std::ostream &os, const Node &rhs)
{
	// os << "v:" << std::setw(2) << rhs._val << " ";
	// if (!rhs._subChains.empty())
	// 	os << "s:" << std::setw(2) << rhs._subChains.back()->_val;
	// os << " ";
	os << rhs.getVal();
	return os;
}