#include "RPN.hpp"

#include <sstream>
#include <iostream>

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

void RPN::calcPush(long long rVal, char ope, long long lVal)
{
	long long res;
	if (ope == '+')
		res = lVal + rVal;
	else if (ope == '-')
		res = lVal - rVal;
	else if (ope == '*')
		res = lVal * rVal;
	else {
		if (rVal == 0)
			throw std::logic_error("Error");
		res = lVal / rVal;
		;
	}

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
			calcPush(pop(), c, pop());
		} else
			throw std::logic_error("Error");
	}

	if (!ss.eof())
		throw std::logic_error("Error");
	if (_stack.size() != 1)
		throw std::logic_error("Error");
	std::cout << pop() << "\n";
}