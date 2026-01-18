#pragma once

#include "Data/Faculty.hpp"


// Объект, позволяющий сохранять и загружать данные факультета
class IFacultyStorage {
public:
	virtual void Save(std::shared_ptr<Faculty> faculty) = 0;
	virtual std::shared_ptr<Faculty> Load() = 0;

	virtual ~IFacultyStorage() {}
};
