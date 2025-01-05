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
	_subChainPtrs = other._subChainPtrs;
	return *this;
}

VNode *VNode::popSubChainPtr()
{
	if (_subChainPtrs.empty())
		throw std::logic_error("subChainPtrs is empty");

	VNode *res = _subChainPtrs.back();
	_subChainPtrs.pop_back();
	return res;
}

void VNode::pushSubChainPtr(VNode *subChainPtr)
{
	if (!subChainPtr)
		throw std::logic_error("subChainPtr is NULL");

	_subChainPtrs.push_back(subChainPtr);
}
