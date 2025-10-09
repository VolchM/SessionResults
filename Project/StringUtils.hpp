#pragma once

#include <string>


namespace StringUtils {
	// Возвращает содержит ли строка пробелы
	bool ContainsSpaces(const std::string& s);

	// Возвращает true, если строка содержит пробелы или пуста
	bool ConstainsSpacesOrEmpty(const std::string& s);

	// Убирает пробелы в начале и конце строки
	std::string Trim(const std::string& s);
}
