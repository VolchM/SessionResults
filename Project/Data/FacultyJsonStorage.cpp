#include "Data/FacultyJsonStorage.hpp"

#include "Data/JsonConvert.hpp"

#include <fstream>


FacultyJsonStorage::FacultyJsonStorage(const std::string& fileName) {
	m_fileName = fileName;
}

void FacultyJsonStorage::Save(std::shared_ptr<Faculty> faculty) {
	nlohmann::json j = faculty;
	std::ofstream fout(m_fileName);
	fout << j.dump(2);
}

std::shared_ptr<Faculty> FacultyJsonStorage::Load() {
	std::ifstream fin(m_fileName);
	std::string content{
		std::istreambuf_iterator<char>(fin),
		std::istreambuf_iterator<char>()
	};
	return nlohmann::json::parse(content);
}
