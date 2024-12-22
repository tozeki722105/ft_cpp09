#ifndef NODE_HPP
#define NODE_HPP

#include <list>
#include <vector>

class Node
{
public:
	size_t _index;
	std::list<std::vector<Node>::iterator> _subChainLinks;

	Node();
	Node(int val);
	~Node();
	Node(const Node &other);
	const Node &operator=(const Node &other);

	int val() const;

	bool operator<(const Node &rhs) const;

private:
	int _val;
};

Node::Node() : _val(0), _index(0) {}

Node::Node(int val) : _val(val), _index(0) {}

Node::~Node() {};

Node::Node(const Node &other)
{
	*this = other;
}

const Node &Node::operator=(const Node &other)
{
	if (this == &other)
		return *this;
	_index = other._index;
	_val = other._val;
	_subChainLinks = other._subChainLinks;
	return *this;
}

int Node::val() const
{
	return _val;
}

bool Node::operator<(const Node &rhs) const
{
	return _val < rhs._val;
}

#include <iomanip>

// std::ostream &operator<<(std::ostream &os, const Node &rhs);
std::ostream &operator<<(std::ostream &os, const Node &rhs)
{
	os << "index: " << std::setw(2) << rhs._index << "; val: " << rhs.val() << ";";
	return os;
}

bool isEvenIndex(Node &node)
{
	return node._index % 2 == 0;
}

bool isOddIndex(Node &node)
{
	return node._index % 2 != 0;
}

#endif