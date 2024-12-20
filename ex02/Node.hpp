#ifndef NODE_HPP
#define NODE_HPP

#include <cstddef>
#include <vector>

class Node
{
public:
	Node();
	Node(int val);
	~Node();
	Node(const Node &other);
	const Node &operator=(const Node &other);

	int val() const;

	bool operator<(const Node &rhs) const;

private:
	int _val;
	std::vector<std::vector<Node>::iterator> _subChainLinks;
};

std::ostream &operator<<(std::ostream &os, const Node &rhs);

Node::Node() : _val(0) {}

Node::Node(int val) : _val(val) {}

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

std::ostream &operator<<(std::ostream &os, const Node &rhs)
{
	os << rhs.val();
	return os;
}

#endif