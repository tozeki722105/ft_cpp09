#include "RPN.hpp"

#include <iostream>
#include <sstream>
#include <limits>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &other)
{
	*this = other;
}

const RPN &RPN::operator=(const RPN &other)
{
	if (this == &other)
		return *this;
	_stack = other._stack;
	return *this;
}

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::pop()
{
	int res = _stack.top();
	_stack.pop();
	return res;
}

void RPN::push(int val)
{
	_stack.push(val);
}

/// @param right,left int型だと ./RPN "0 2 - 8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 0 1 - /"
/// でクラッシュする
void RPN::calcPush(long long left, char ope, long long right)
{
	long long res;
	if (ope == '+')
		res = left + right;
	else if (ope == '-')
		res = left - right;
	else if (ope == '*')
		res = left * right;
	else {
		if (right == 0)  // 0で割るときはエラー
			throw std::logic_error("Error");
		res = left / right;
	}

	// intオーバーフローしたら、エラー
	if (res < std::numeric_limits<int>::min() || std::numeric_limits<int>::max() < res)
		throw std::logic_error("Error");
	push(static_cast<int>(res));
}

void RPN::exec(char *RPNStr)
{
	if (*RPNStr == '\0')
		throw std::logic_error("Error");

	std::stringstream ss(RPNStr);
	char c;
	while (ss >> c) {
		if (std::isdigit(c))
			push(c - '0');
		else if (isOperator(c)) {
			if (_stack.size() < 2)
				throw std::logic_error("Error");
			int right = pop();
			int left = pop();
			calcPush(left, c, right);
		} else
			throw std::logic_error("Error");
	}

	if (!ss.eof())  // char型への変換が失敗してwhileを抜けたとき
		throw std::logic_error("Error");
	if (_stack.size() != 1)
		throw std::logic_error("Error");
	std::cout << pop() << "\n";
}