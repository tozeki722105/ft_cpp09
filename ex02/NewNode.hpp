#ifndef NODE_HPP
#define NODE_HPP

#include <list>
#include <vector>

class Node
{
public:
	int _val;
	std::list<Node *> _subChainLinks;
	bool _mainChainFlag;

	Node();
	Node(int val);
	~Node();
	Node(const Node &other);
	const Node &operator=(const Node &other);

	bool operator<(const Node &rhs) const;
};

Node::Node() : _val(0), _mainChainFlag(false) {}

Node::Node(int val) : _val(val), _mainChainFlag(false) {}

Node::~Node() {};

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
	_subChainLinks = other._subChainLinks;
	return *this;
}

bool Node::operator<(const Node &rhs) const
{
	// static size_t count = 1;
	// std::cout << "comp: " << count++ << "\n";
	return _val < rhs._val;
}

#include <iomanip>

// std::ostream &operator<<(std::ostream &os, const Node &rhs);
std::ostream &operator<<(std::ostream &os, const Node &rhs)
{
	os << "val: " << std::setw(2) << rhs._val << ";";
	return os;
}

bool isMainChain(Node &node)
{
	return node._mainChainFlag;
}

#endif