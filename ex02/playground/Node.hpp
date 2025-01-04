#ifndef NODE_HPP
#define NODE_HPP

class Node
{
public:
	Node();
	Node(int val);
	~Node();
	Node(const Node &other);
	const Node &operator=(const Node &other);

	// getter
	int getVal() const;
	bool getMainChainFlag() const;
	// setter
	void setMainChainFlag(bool val);

	// size_t resetCompCount();
	bool operator<(const Node &rhs) const;

private:
	int _val;
	bool _mainChainFlag;

	// static size_t _cmpCount;  // 比較をカウントする静的メンバ変数
};

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

// size_t Node::resetCompCount()
// {
// 	size_t res = _cmpCount;
// 	_cmpCount = 0;
// 	return res;
// }

bool Node::operator<(const Node &rhs) const
{
	_cmpCount++;
	return _val < rhs._val;
}

bool isMainChain(Node &node)
{
	return node.getMainChainFlag();
}

#include <iomanip>

std::ostream &operator<<(std::ostream &os, const Node &rhs)
{
	// os << "v:" << std::setw(2) << rhs._val << " ";
	// if (!rhs._subChainPtrs.empty())
	// 	os << "s:" << std::setw(2) << rhs._subChainPtrs.back()->_val;
	// os << " ";
	os << rhs.getVal();
	return os;
}

#endif