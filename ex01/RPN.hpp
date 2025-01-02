#ifndef RPN_HPP
#define RPN_HPP

#include <stack>

class RPN
{
public:
	RPN();
	~RPN();
	void exec(char *RPNStr);

private:
	std::stack<int> _stack;

	bool isOperator(char c) const;
	int pop();
	void push(int val);
	void calcPush(long long rVal, char ope, long long lVal);
};

#endif