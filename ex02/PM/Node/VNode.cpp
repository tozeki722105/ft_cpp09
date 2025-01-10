#include "VNode.hpp"

VNode::VNode(int val) : Node(val) {}

VNode::~VNode() {}

VNode::VNode(const VNode &other)
{
	*this = other;
}

const VNode &VNode::operator=(const VNode &other)
{
	if (this == &other)
		return *this;
	Node::operator=(other);
	_subChains = other._subChains;
	return *this;
}

VNode *VNode::popSubChain()
{
	if (_subChains.empty())
		throw std::logic_error("subChains is empty");

	VNode *res = _subChains.back();
	_subChains.pop_back();
	return res;
}

void VNode::pushSubChain(VNode *subChainPtr)
{
	if (!subChainPtr)
		throw std::logic_error("subChainPtr is NULL");

	_subChains.push_back(subChainPtr);
}
