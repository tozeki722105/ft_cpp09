#ifndef VNODE_HPP
#define VNODE_HPP

#include <vector>

#include "Node.hpp"

class VNode : public Node
{
public:
	VNode(int val);
	virtual ~VNode();
	VNode(const VNode &other);
	const VNode &operator=(const VNode &other);

	// getter
	VNode *popSubChainPtr();
	// setter
	void pushSubChainPtr(VNode *subChainNode);

private:
	VNode();
	std::vector<VNode *> _subChainPtrs;
};

#endif