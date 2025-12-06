#include "Rectangle.hpp"

#include <iostream>
#include <format>


consteval int factorial(int n) {
	if (n <= 1) return 1;
	return n * factorial(n - 1);
}


constexpr Rectangle modify_rect_example(int n) {
	Rectangle rect(0, 0, 10, 10);

	rect.set_width(n);
	rect.set_height(n);

	return rect;
}

constinit Rectangle global_rect = Rectangle(0, 0, 1, 1);

Rectangle next_rect() {
	global_rect.set_x(global_rect.get_x() + 1);
	global_rect.set_y(global_rect.get_y() + 1);
	return global_rect;
}


int main() {
	setlocale(LC_ALL, "Rus");

	constexpr int n = 10;
	constexpr int fact_n = factorial(n);
	std::cout << std::format("Вычисление на этапе компиляции: factorial({}) = {}", n, fact_n) << std::endl;
	std::cout << std::endl;


	constexpr Rectangle rect1 = Rectangle::from_points(2, 4, 3, -1);
	std::cout << "Константный rect1, созданный на этапе компиляции: " << rect1 << std::endl;

	constexpr int area1 = rect1.area();
	std::cout << "Площадь rect1: " << area1 << std::endl;
	std::cout << std::endl;


	constexpr Rectangle rect2 = modify_rect_example(3);
	std::cout << "Объект rect2, полученный после изменения внутри constexpr-функции: " << rect2 << std::endl;
	std::cout << "Вычисление на этапе компиляции: factorial(rect2.area()) = " << factorial(rect2.area()) << std::endl;

	constexpr bool overlap12 = rect1.overlaps(rect2);
	std::cout << std::format("rect1.overlaps(rect2): {}", overlap12) << std::endl;
	std::cout << std::endl;


	std::cout << "Изменение constinit-объекта, инициализированного на этапе компиляции:" << std::endl;
	std::cout << next_rect().to_string(true) << ";  " << next_rect().to_string(true) << ";  " << next_rect().to_string(true) << std::endl;
	std::cout << std::endl;


	int input_size;
	std::cout << "Введите длину стороны квадрата: ";
	std::cin >> input_size;

	Rectangle rect3(0, 0, input_size, input_size);
	std::cout << "Объект rect3, созданный в ходе выполнения: " << rect3 << ", площадь:" << rect3.area() << std::endl;

	std::cout << std::format("rect1.overlaps(rect3) = {}", rect1.overlaps(rect3)) << std::endl;
}
