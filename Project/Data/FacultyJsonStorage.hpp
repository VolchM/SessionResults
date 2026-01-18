#pragma once

#include "Data/IFacultyStorage.hpp"
#include "Data/Faculty.hpp"


class FacultyJsonStorage : public IFacultyStorage {
private:
	std::string m_fileName;

public:
	FacultyJsonStorage(const std::string& fileName);

	void Save(std::shared_ptr<Faculty> faculty) override;
	std::shared_ptr<Faculty> Load() override;
};
