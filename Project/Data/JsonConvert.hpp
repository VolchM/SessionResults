#pragma once

#include "Faculty.hpp"

#include <memory>
#include <string>
#include <vector>

#include "Lib/json.hpp"


std::string ConvertCP1251ToUTF8(const std::string& str);
std::string ConvertUTF8ToCP1251(const std::string& str);

// Функции преобразования объектов в JSON
void to_json(nlohmann::json& j, const std::shared_ptr<Discipline>& discipline);
void to_json(nlohmann::json& j, const DisciplineList& disciplineList);
void to_json(nlohmann::json& j, const SessionResults& sessionResults);
void to_json(nlohmann::json& j, const std::shared_ptr<Student>& student);
void to_json(nlohmann::json& j, const std::shared_ptr<Group>& group);
void to_json(nlohmann::json& j, const std::shared_ptr<Speciality>& speciality);
void to_json(nlohmann::json& j, const std::shared_ptr<Faculty>& faculty);

// Функции преобразования JSON в объекты
void from_json(const nlohmann::json& j, std::shared_ptr<Discipline>& discipline);
void from_json(const nlohmann::json& j, DisciplineList& disciplineList);
void from_json(const nlohmann::json& j, SessionResults& sessionResults);
void from_json(const nlohmann::json& j, std::shared_ptr<Student>& student);
void from_json(const nlohmann::json& j, std::shared_ptr<Group>& group);
void from_json(const nlohmann::json& j, std::shared_ptr<Speciality>& speciality);
void from_json(const nlohmann::json& j, std::shared_ptr<Faculty>& faculty);
