#include <iostream>
#include <tuple>


// ####################### Iterate tuple by members #######################
template<size_t I = 0, typename ...Ts>
std::enable_if_t<I == sizeof...(Ts)> print_tuple(const std::tuple<Ts...>&) {}


template<size_t I = 0, typename ...Ts>
std::enable_if_t<I < sizeof...(Ts)> print_tuple(const std::tuple<Ts...>& tuple) {
	std::cout << std::get<I>(tuple) << std::endl;
	print_tuple<I+1, Ts...>(tuple);
}


// ####################### Iterate tuple by size #######################
template<typename T>
T inc_member(const T& t) {
	return t + 1;
}

template<std::size_t ...I, typename ...Ts>
std::tuple<Ts...> inc_tuple_impl(
	[[maybe_unused]] std::index_sequence<I...>,
	const std::tuple<Ts...>& t
) {
	return std::make_tuple(inc_member(std::get<I>(t)) ...);
}

template<typename ...Ts>
std::tuple<Ts...> inc_tuple(const std::tuple<Ts...>& t) {
	return inc_tuple_impl(std::make_index_sequence<sizeof...(Ts)>(), t);
}

int main() {
	using t_type = std::tuple<int, float, double, unsigned int>;
	t_type t = std::make_tuple(42, 3.1415f, 54.0, 5);

	std::cout << "created tuple: " << std::endl;
	print_tuple(t);

	std::cout << "incremented elements by one:" << std::endl;
	t_type t_inc = inc_tuple(t);
	print_tuple(t_inc);

}
