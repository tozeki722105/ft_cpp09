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
	return *this;
}

int Node::getVal() const
{
	return _val;
}

bool Node::getMainChainFlag() const
{
	return _mainChainFlag;
}

void Node::setMainChainFlag(bool val)
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

bool isMainChain(Node &node)
{
	return node.getMainChainFlag();
}

std::ostream &operator<<(std::ostream &os, const Node &rhs)
{
	// os << "v:" << std::setw(2) << rhs._val << " ";
	// if (!rhs._subChainPtrs.empty())
	// 	os << "s:" << std::setw(2) << rhs._subChainPtrs.back()->_val;
	// os << " ";
	os << rhs.getVal();
	return os;
}