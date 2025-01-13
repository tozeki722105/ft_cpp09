#include "RPN.hpp"

#include <iostream>
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
	if (res < static_cast<long long>(std::numeric_limits<int>::min()) ||
			static_cast<long long>(std::numeric_limits<int>::max()) < res)
		throw std::logic_error("Error");
	push(static_cast<int>(res));
}

void RPN::exec(char *RPNStr)
{
	if (*RPNStr == '\0')
		throw std::logic_error("Error");

	size_t i = 0;
	size_t next = 1;
	while ((std::isdigit(RPNStr[i]) || isOperator(RPNStr[i])) &&
			(RPNStr[next] == ' ' || !RPNStr[next])) {
		if (isOperator(RPNStr[i])) {
			if (_stack.size() < 2)
				throw std::logic_error("Error");
			int right = pop();
			int left = pop();
			calcPush(left, RPNStr[i], right);
		} else
			push(RPNStr[i] - '0');
		if (!RPNStr[next])
			break;
		i += 2;
		next += 2;
	}

	if (RPNStr[next])
		throw std::logic_error("Error");
	if (_stack.size() != 1)
		throw std::logic_error("Error");
	std::cout << pop() << "\n";
}