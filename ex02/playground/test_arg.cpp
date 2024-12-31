#include <vector>

#include <sstream>
#include <iostream>

// "program_name", ""
// ./a.out ""
// ./a.out "123 456"
// ./a.out "-123"
// ./a.out "4294967296"
// ./a.out "123a"
// ./a.out " 123"
// ./a.out "123 "

void tryArg(int argc, char** argv, std::vector<unsigned int>& _arg)
{
	std::stringstream ss;
	unsigned int val;
	for (size_t i = 1; i < argc; i++) {
		if (argv[i][0] == '\0')
			throw std::runtime_error("Invalid argment");
		ss << argv[i];
		if (!(ss >> val) || !ss.eof())
			throw std::runtime_error("Invalid argment");
		ss.clear();
		_arg.push_back(val);
	}
}

int main(int argc, char** argv)
{
	std::vector<unsigned int> _arg;
	_arg.reserve(argc - 1);

	try {
		tryArg(argc, argv, _arg);
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}