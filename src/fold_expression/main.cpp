#include <iostream>
#include <tuple>

template <typename ...Ts>
auto add(Ts&&... args)
{
	return (args + ...);
}

template <typename ...Ts>
void cout(Ts&&... args)
{
	(std::cout << ... << args) << std::endl;
}

template <typename T, typename ...Fs>
void invoke_different_functions(const T& arg, Fs... functions)
{
	(functions(arg), ...);
}

template <typename F, typename ...Ts>
void invoke_same_function(F function, Ts&&... args)
{
	(function(std::forward<Ts>(args)), ...);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	std::cout << "add values with auto return type (1, .5f, 2): " << add(1, .5f, 2) << std::endl;

	std::cout << "cout values (0, 1.1f, -.03, \"str\"): ";
	cout(0, 1.1f, -.03, "str");

	std::cout << "invoking different functions with the same arg (42.): " << std::endl;
	float x = 1.;
	invoke_different_functions(42., 
		[] (float f) { std::cout << "\tsome squaring function (f * f): " << (f * f) << std::endl; },
		[x] (float f) { std::cout << "\tsome statefull function (f + x): " << (f + x) << std::endl; }
	);

	std::cout << "invoking same function with different args (3, -5): " << std::endl;
	invoke_same_function([] (int i) { std::cout << "\tsome squaring function (i * i): " << (i * i) << std::endl; },
			3,
			-5
	);

	return 0;
}
