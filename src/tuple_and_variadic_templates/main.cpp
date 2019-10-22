#include <iostream>
#include <tuple>


// Iterate tuple

template<size_t I = 0, typename ...Ts>
std::enable_if_t<I == sizeof...(Ts)> iterate_tuple(const std::tuple<Ts...>&) {}


template<size_t I = 0, typename ...Ts>
std::enable_if_t<I < sizeof...(Ts)> iterate_tuple(const std::tuple<Ts...>& tuple) {
	std::cout << std::get<I>(tuple) << std::endl;
	iterate_tuple<I+1, Ts...>(tuple);
}


int main() {
	std::tuple<int, float> t = std::make_tuple(42, 3.1415f);
	iterate_tuple(t);
}
