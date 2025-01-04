#ifndef LNODE_HPP
#define LNODE_HPP

#include <list>

class LNode
{
public:
	LNode();
	LNode(int val);
	~LNode();
	LNode(const LNode &other);
	const LNode &operator=(const LNode &other);

	// getter
	int getVal() const;
	bool getMainChainFlag() const;
	LNode *popSubChainPtr();
	// setter
	void setMainChainFlag(bool val);
	void pushSubChainPtr(LNode *subChainNode);

	size_t resetCompCount();
	bool operator<(const LNode &rhs) const;

private:
	int _val;
	bool _mainChainFlag;
	std::list<LNode *> _subChainPtrs;  ///

	static size_t _cmpCount;  // 比較をカウントする静的メンバ変数
};

LNode::LNode() : _mainChainFlag(true) {}

LNode::LNode(int val) : _val(val), _mainChainFlag(true) {}

LNode::~LNode() {}

LNode::LNode(const LNode &other)
{
	*this = other;
}

const LNode &LNode::operator=(const LNode &other)
{
	if (this == &other)
		return *this;
	_val = other._val;
	_subChainPtrs = other._subChainPtrs;
	_mainChainFlag = other._mainChainFlag;
	return *this;
}

int LNode::getVal() const
{
	return _val;
}

bool LNode::getMainChainFlag() const
{
	return _mainChainFlag;
}

LNode *LNode::popSubChainPtr()
{
	if (_subChainPtrs.empty())
		throw std::logic_error("subChainPtrs is empty");

	LNode *res = _subChainPtrs.back();
	_subChainPtrs.pop_back();
	return res;
}

void LNode::setMainChainFlag(bool val)
{
	_mainChainFlag = val;
}

void LNode::pushSubChainPtr(LNode *subChainPtr)
{
	if (!subChainPtr)
		throw std::logic_error("subChainNode is NULL");

	_subChainPtrs.push_back(subChainPtr);
}

size_t LNode::resetCompCount()
{
	size_t res = _cmpCount;
	_cmpCount = 0;
	return res;
}

bool LNode::operator<(const LNode &rhs) const
{
	_cmpCount++;
	return _val < rhs._val;
}

bool isLMainChain(LNode &node)
{
	return node.getMainChainFlag();
}

#include <iomanip>

std::ostream &operator<<(std::ostream &os, const LNode &rhs)
{
	// os << "v:" << std::setw(2) << rhs._val << " ";
	// if (!rhs._subChainPtrs.empty())
	// 	os << "s:" << std::setw(2) << rhs._subChainPtrs.back()->_val;
	// os << " ";
	os << rhs.getVal();
	return os;
}

#endif