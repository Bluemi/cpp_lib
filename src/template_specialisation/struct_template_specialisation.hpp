#include <iostream>
#include <tuple>

template<typename ComponentType, typename __Specialization=void>
struct base {
	void foo() { std::cout << "base" << std::endl; }
};

template<typename RelationType>
struct base<RelationType, std::enable_if_t<std::is_arithmetic_v<RelationType>>> {
	void foo() { std::cout << "specialization" << std::endl; }
};

void test_struct_template_specialisation()
{
	base<std::string> c;
	c.foo();

	base<float> b;
	b.foo();
}
