#include "function_template_specialisation.hpp"
#include "struct_template_specialisation.hpp"

#include <iostream>

int main() {
	std::cout << "---------------- struct_template_specialisation ------------------" << std::endl;
	test_struct_template_specialisation();
	std::cout << std::endl;

	std::cout << "---------------- function_template_specialisation ----------------" << std::endl;
	test_function_template_specialisation();
	std::cout << std::endl;
}
