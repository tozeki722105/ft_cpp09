#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <list>

#include "stddef.h"

class Node
{
public:
	Node();
	Node(int val);
	virtual ~Node();
	Node(const Node &other);
	const Node &operator=(const Node &other);

	// getter
	int getVal() const;
	bool isMainChain() const;
	// setter
	void setMainChain(bool val);

	size_t resetCompCount();
	bool operator<(const Node &rhs) const;

	// getter
	Node *popSubChain();
	// setter
	void pushSubChain(Node *subChainNode);

private:
	int _val;
	bool _mainChainFlag;
	std::list<Node *> _subChains;  // ここの型だけ違う

	static size_t _cmpCount;  // 比較をカウントする静的メンバ変数
};

bool isMainChain(Node &node);
std::ostream &operator<<(std::ostream &os, const Node &rhs);

#endif