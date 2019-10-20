#include <iostream>
#include <tuple>

template<typename T, typename S=void>
struct base {
	void foo() { std::cout << "base" << std::endl; }
};

template<typename T>
struct base<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
	void foo() { std::cout << "specialization" << std::endl; }
};

void test_struct_template_specialisation()
{
	base<std::string> c;
	c.foo();

	base<float> b;
	b.foo();
}
