#ifndef LNODE_HPP
#define LNODE_HPP

#include <list>
#include "Node.hpp"

class LNode : public Node
{
public:
	LNode();
	LNode(int val);
	~LNode();
	LNode(const LNode &other);
	const LNode &operator=(const LNode &other);

	// getter
	LNode *popSubChainPtr();
	// setter
	void pushSubChainPtr(LNode *subChainNode);

private:
	std::list<LNode *> _subChainPtrs;
};

#endif