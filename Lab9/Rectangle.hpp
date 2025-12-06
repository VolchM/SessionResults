#pragma once

#include <iostream>
#include <string>
#include <format>


constexpr int c_abs(int n) {
	return n < 0 ? -n : n;
}


class Rectangle {
private:
	int m_x, m_y;
	int m_width, m_height;
public:
	constexpr Rectangle(int x, int y, int width, int height) {
		if (width <= 0 || height <= 0) {
			throw std::invalid_argument("Rectangle width and height can't be equal or less than zero");
		}
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
	}

	constexpr void set_x(int x) {
		m_x = x;
	}
	constexpr void set_y(int y) {
		m_y = y;
	}
	constexpr void set_width(int width) {
		if (width <= 0) {
			throw std::invalid_argument("Rectangle width can't be equal or less than zero");
		}
		m_width = width;
	}
	constexpr void set_height(int height) {
		if (height <= 0) {
			throw std::invalid_argument("Rectangle height can't be equal or less than zero");
		}
		m_height = height;
	}

	constexpr int get_x() const { return m_x; }
	constexpr int get_y() const { return m_y; }
	constexpr int get_width() const { return m_width; }
	constexpr int get_height() const { return m_height; }

	constexpr int get_x2() const { return m_x + m_width; }
	constexpr int get_y2() const { return m_y + m_height; }

	constexpr int area() const {
		return m_width * m_height;
	}

	constexpr bool overlaps(const Rectangle& other) const {
		return this->get_x2() > other.get_x()
			&& this->get_x() < other.get_x2()
			&& this->get_y2() > other.get_y()
			&& this->get_y() < other.get_y2();
	}

	std::string to_string(bool compact = false) const {
		if (!compact) {
			return std::format("Rectangle(x={0}, y={1}, width={2}, height={3})", m_x, m_y, m_width, m_height);
		} else {
			return std::format("{2}x{3} at ({0},{1})", m_x, m_y, m_width, m_height);
		}
	}


	static constexpr Rectangle from_points(int x1, int y1, int x2, int y2) {
		if (x1 == x2 || y1 == y2) {
			throw std::invalid_argument("x and y coordinates of points can't be equal to each other");
		}
		return Rectangle(std::min(x1, x2), std::min(y1, y2), c_abs(x1 - x2), c_abs(y1 - y2));
	}
};

std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
	return os << rect.to_string();
}
