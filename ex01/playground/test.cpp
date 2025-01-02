#include <sstream>
#include <string>
#include <stack>
#include <iostream>

int main(int argc, char **argv)
{
	char val;
	std::stringstream ss(argv[1]);
	while (ss >> val) {
		std::cout << val << ";" << std::endl;
	}
}

// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return 1;

// 	std::stack<int> stack;
// 	std::stringstream ss(argv[1]);
// 	char val;
// 	size_t i = 0;
// 	while (ss >> val) {
// 		if (std::isdigit(val))
// 			stack.push(val - '0');
// 		else if (isOperator(val)) {
// 			if (stack.size() < 2)
// 				throw std::logic_error("error: ");
// 			calc_push(stack.pop(), val, stack.pop());
// 		} else
// 			throw std::logic_error("error: ");
// 		i++;
// 	}
// 	if (!ss.eof())
// 		throw std::logic_error("error: ");
// 	if (stack.size() != 1)
// 		throw std::logic_error("error: ");
// }
