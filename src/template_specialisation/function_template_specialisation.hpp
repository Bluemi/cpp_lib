#include <iostream>
#include <tuple>

template<typename ComponentType>
std::enable_if_t<!std::is_arithmetic_v<ComponentType>> foo(ComponentType) {
	std::cout << "base" << std::endl;
}

template<typename RelationType>
std::enable_if_t<std::is_arithmetic_v<RelationType>> foo(RelationType) {
	std::cout << "special" << std::endl;
}

void test_function_template_specialisation()
{
	std::string s("heyhey");
	std::cout << "foo(string): ";
	foo(s);

	std::cout << "foo(int): ";
	int i = 42;
	foo(i);
}
