#ifndef LNODE_HPP
#define LNODE_HPP

#include <list>

#include "Node.hpp"

class LNode : public Node
{
public:
	LNode(int val);
	virtual ~LNode();
	LNode(const LNode &other);
	const LNode &operator=(const LNode &other);

	// getter
	LNode *popSubChain();
	// setter
	void pushSubChain(LNode *subChainNode);

private:
	LNode();
	std::list<LNode *> _subChains;  // ここの型だけ違う
};

#endif