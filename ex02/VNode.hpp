#ifndef VNODE_HPP
#define VNODE_HPP

#include <vector>

class VNode
{
public:
	VNode();
	VNode(int val);
	~VNode();
	VNode(const VNode &other);
	const VNode &operator=(const VNode &other);

	// getter
	int getVal() const;
	bool getMainChainFlag() const;
	VNode *popSubChainPtr();
	// setter
	void setMainChainFlag(bool val);
	void pushSubChainPtr(VNode *subChainNode);

	size_t resetCompCount();
	bool operator<(const VNode &rhs) const;

private:
	int _val;
	bool _mainChainFlag;
	std::vector<VNode *> _subChainPtrs;  ///

	static size_t _cmpCount;  // 比較をカウントする静的メンバ変数
};

VNode::VNode() : _mainChainFlag(true) {}  ////

VNode::VNode(int val) : _val(val), _mainChainFlag(true) {}

VNode::~VNode() {}

VNode::VNode(const VNode &other)
{
	*this = other;
}

const VNode &VNode::operator=(const VNode &other)
{
	if (this == &other)
		return *this;
	_val = other._val;
	_subChainPtrs = other._subChainPtrs;
	_mainChainFlag = other._mainChainFlag;
	return *this;
}

int VNode::getVal() const
{
	return _val;
}

bool VNode::getMainChainFlag() const
{
	return _mainChainFlag;
}

VNode *VNode::popSubChainPtr()
{
	if (_subChainPtrs.empty())
		throw std::logic_error("subChainPtrs is empty");

	VNode *res = _subChainPtrs.back();
	_subChainPtrs.pop_back();
	return res;
}

void VNode::setMainChainFlag(bool val)
{
	_mainChainFlag = val;
}

void VNode::pushSubChainPtr(VNode *subChainPtr)
{
	if (!subChainPtr)
		throw std::logic_error("subChainNode is NULL");

	_subChainPtrs.push_back(subChainPtr);
}

size_t VNode::resetCompCount()
{
	size_t res = _cmpCount;
	_cmpCount = 0;
	return res;
}

bool VNode::operator<(const VNode &rhs) const
{
	_cmpCount++;
	std::cout << _cmpCount << "回目\n";
	return _val < rhs._val;
}

bool isVMainChain(VNode &node)
{
	return node.getMainChainFlag();
}

#include <iomanip>

std::ostream &operator<<(std::ostream &os, const VNode &rhs)
{
	// os << "v:" << std::setw(2) << rhs._val << " ";
	// if (!rhs._subChainPtrs.empty())
	// 	os << "s:" << std::setw(2) << rhs._subChainPtrs.back()->_val;
	// os << " ";
	os << rhs.getVal();
	return os;
}

#endif