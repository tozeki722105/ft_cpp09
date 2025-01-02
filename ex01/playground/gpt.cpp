#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>  // for std::atoi

bool isOperator(const std::string& token)
{
	return token == "+" || token == "-" || token == "*" || token == "/";
}

int performOperation(const std::string& op, int a, int b)
{
	if (op == "+")
		return a + b;
	if (op == "-")
		return a - b;
	if (op == "*")
		return a * b;
	if (op == "/") {
		if (b == 0) {
			throw std::runtime_error("Error: Division by zero");
		}
		return a / b;
	}
	throw std::runtime_error("Error: Unknown operator");
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <RPN expression>\n";
		return 1;
	}

	std::stack<int> stack;

	try {
		for (int i = 1; i < argc; ++i) {
			std::string token(argv[i]);

			if (isOperator(token)) {
				if (stack.size() < 2) {
					throw std::runtime_error("Error: Insufficient operands for operation");
				}
				int b = stack.top();
				stack.pop();
				int a = stack.top();
				stack.pop();
				int result = performOperation(token, a, b);
				stack.push(result);
			} else {
				// Assume the token is an integer
				int value = std::atoi(token.c_str());
				stack.push(value);
			}
		}

		if (stack.size() != 1) {
			throw std::runtime_error("Error: Malformed RPN expression");
		}

		std::cout << "Result: " << stack.top() << std::endl;

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
