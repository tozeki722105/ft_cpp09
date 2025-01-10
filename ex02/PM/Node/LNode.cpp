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
	_subChains = other._subChains;
	return *this;
}

LNode *LNode::popSubChain()
{
	if (_subChains.empty())
		throw std::logic_error("subChains is empty");

	LNode *res = _subChains.back();
	_subChains.pop_back();
	return res;
}

void LNode::pushSubChain(LNode *subChainPtr)
{
	if (!subChainPtr)
		throw std::logic_error("subChainPtr is NULL");

	_subChains.push_back(subChainPtr);
}
