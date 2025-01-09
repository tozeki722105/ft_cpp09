#include "LNode.hpp"

LNode::LNode(int val) : Node(val) {}

LNode::~LNode() {}

LNode::LNode(const LNode &other)
{
	*this = other;
}

const LNode &LNode::operator=(const LNode &other)
{
	if (this == &other)
		return *this;
	Node::operator=(other);
	_subChainPtrs = other._subChainPtrs;
	return *this;
}

LNode *LNode::popSubChainPtr()
{
	if (_subChainPtrs.empty())
		throw std::logic_error("subChainPtrs is empty");

	LNode *res = _subChainPtrs.back();
	_subChainPtrs.pop_back();
	return res;
}

void LNode::pushSubChainPtr(LNode *subChainPtr)
{
	if (!subChainPtr)
		throw std::logic_error("subChainPtr is NULL");

	_subChainPtrs.push_back(subChainPtr);
}
