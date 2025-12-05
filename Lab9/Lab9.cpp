#include <iostream>
#include <format>

consteval int factorial(int n) {
	if (n <= 1) return 1;
	return n * factorial(n - 1);
}

int main() {
	setlocale(LC_ALL, "Rus");

	constexpr int n = 10;
	constexpr int fact_n = factorial(n);
	std::cout << std::format("Вычисление на этапе компиляции: factorial({}) = {}", n, fact_n) << std::endl;
}
