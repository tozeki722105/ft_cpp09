#ifndef MYPAIR_HPP
#define MYPAIR_HPP

#include <cstddef>
#include <exception>

class Chain
{
public:
	Chain(int val, Chain *subChain = NULL);
	~Chain();
	int val() const;
	const Chain *subChain() const;
	void Chain::swap();
private:
	// void setVal(int val);
	int _val;
	Chain *_subChain;
};

Chain::Chain(int val, Chain *subChain) : _val(val), _subChain(subChain) {}

Chain::~Chain() {}

int Chain::val() const
{
	return _val;
}

const Chain *Chain::subChain() const
{
	return _subChain;
}

// void Chain::setVal(int val)
// {
// 	_val = val;
// }

void Chain::swap()
{
	if (!_subChain)
		throw std::exception();
	if (_subChain->val() <= _val)
		return ;
	int tmp = _subChain->val();
	_subChain->_val = this->_val; //エラーになるはず？
	this->_val = tmp;
}

#endif