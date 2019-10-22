#include <tuple>
#include <iostream>


struct Base {
	using special = int;
};

template<typename T, typename S=void>
struct a {
	using type = T;
};

template<typename T>
struct a<T, std::enable_if_t<std::is_base_of<Base, T>::value>> {
	using type = typename T::special;
};


/*
template<typename T>
using a = std::conditional_t<std::is_base_of_v<Base, T>, Base::special, T>;
*/


void test_conditional_types() {
	std::tuple<a<Base>::type, a<float>::type> t = std::make_tuple(42, 3.1415f);
	std::cout << std::get<int>(t) << " " << std::get<float>(t) << std::endl;
}

int main() {
	std::cout << "---------------- conditional_types ----------------" << std::endl;
	test_conditional_types();
	std::cout << std::endl;
}
