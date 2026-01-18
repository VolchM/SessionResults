#include "Data/JsonConvert.hpp"

#include <Windows.h>


using json = nlohmann::json;


std::string ConvertCP1251ToUTF8(const std::string& str) {
    int len = MultiByteToWideChar(1251, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(1251, 0, str.c_str(), -1, wstr, len);

    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, 0, 0);
    char* utf8 = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, 0, 0);

    std::string result(utf8);
    delete[] wstr;
    delete[] utf8;

    return result;
}

std::string ConvertUTF8ToCP1251(const std::string& str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, len);

    len = WideCharToMultiByte(1251, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* cp1251 = new char[len];
    WideCharToMultiByte(1251, 0, wstr, -1, cp1251, len, NULL, NULL);

    std::string result(cp1251);
    delete[] wstr;
    delete[] cp1251;

    return result;
}



void to_json(json& j, const std::shared_ptr<Discipline>& discipline) {
    j = json{
        { "Name", ConvertCP1251ToUTF8(discipline->GetName()) },
        { "AttestationType", discipline->GetAttestationType() },
    };
}

void to_json(json& j, const DisciplineList& disciplineList) {
    j = json(disciplineList.GetDisciplines());
}

void to_json(json& j, const SessionResults& sessionResults) {
    std::vector<int> results;
    for (auto& discipline : sessionResults.GetDisciplineList().GetDisciplines()) {
        switch (discipline->GetAttestationType()) {
        case Discipline::AttestationType::eExam:
            results.push_back(sessionResults.GetResult(discipline)->ToScore());
            break;
        case Discipline::AttestationType::ePassFailExam:
            results.push_back(sessionResults.GetResult(discipline)->IsPassed());
            break;
        }
    }

    j = json{
        { "Disciplines", sessionResults.GetDisciplineList() },
        { "Results", results },
    };
}

void to_json(json& j, const std::shared_ptr<Student>& student) {
    j = json{
        { "StudentID", student->GetStudentID() },
        { "FirstName", ConvertCP1251ToUTF8(student->GetFirstName()) },
        { "LastName", ConvertCP1251ToUTF8(student->GetLastName()) },
        { "MiddleName", ConvertCP1251ToUTF8(student->GetMiddleName()) },
        { "SessionResults", student->GetSessionResults() },
    };
}

void to_json(json& j, const std::shared_ptr<Group>& group) {
    j = json{
        { "Name", ConvertCP1251ToUTF8(group->GetName()) },
        { "Course", group->GetCourse() },
        { "Students", group->GetStudents() },
    };
}

void to_json(json& j, const std::shared_ptr<Speciality>& speciality) {
    std::vector<DisciplineList> disciplineLists;
    for (int course = Speciality::MIN_COURSE; course <= Speciality::MAX_COURSE; course++) {
        disciplineLists.push_back(speciality->GetDisciplineList(course));
    }

    j = json{
        { "Code", ConvertCP1251ToUTF8(speciality->GetCode()) },
        { "Name", ConvertCP1251ToUTF8(speciality->GetName()) },
        { "Groups", speciality->GetGroups() },
        { "Disciplines", disciplineLists },
    };
}

void to_json(json& j, const std::shared_ptr<Faculty>& faculty) {
    j = json{
        { "Name", ConvertCP1251ToUTF8(faculty->GetName()) },
        { "Specialities", faculty->GetSpecialities() },
    };
}



void from_json(const json& j, std::shared_ptr<Discipline>& discipline) {
    discipline = std::make_shared<Discipline>(
        ConvertUTF8ToCP1251(j.at("Name")),
        j.at("AttestationType")
    );
}

void from_json(const json& j, DisciplineList& disciplineList) {
    disciplineList = DisciplineList(j.get<std::vector<std::shared_ptr<Discipline>>>());
};

void from_json(const json& j, SessionResults& sessionResults) {
    const DisciplineList& disciplines = j.at("Disciplines");
    const std::vector<int>& results = j.at("Results");

    if (disciplines.GetSize() != results.size()) {
        throw json::other_error::create(503, "SessionResults Disciplines and Results sizes are not equal", nullptr);
    }

    sessionResults = SessionResults();
    for (int i = 0; i < disciplines.GetSize(); i++) {
        switch (disciplines.GetDisciplineAt(i)->GetAttestationType()) {
        case Discipline::AttestationType::eExam:
            sessionResults.SetResult(disciplines.GetDisciplineAt(i), std::make_shared<ExamResult>(results[i]));
            break;
        case Discipline::AttestationType::ePassFailExam:
            sessionResults.SetResult(disciplines.GetDisciplineAt(i), std::make_shared<PassFailExamResult>(results[i]));
            break;
        }
    }
};

void from_json(const json& j, std::shared_ptr<Student>& student) {
    student = std::make_shared<Student>(
        j.at("StudentID"),
        ConvertUTF8ToCP1251(j.at("FirstName")),
        ConvertUTF8ToCP1251(j.at("LastName")),
        ConvertUTF8ToCP1251(j.at("MiddleName"))
    );
    student->GetSessionResults() = j.at("SessionResults");
}

void from_json(const json& j, std::shared_ptr<Group>& group) {
    group = std::make_shared<Group>(
        ConvertUTF8ToCP1251(j.at("Name")),
        j.at("Course")
    );
    for (auto& student : j.at("Students")) {
        group->AddStudent(student);
    }
}

void from_json(const json& j, std::shared_ptr<Speciality>& speciality) {
    speciality = std::make_shared<Speciality>(
        ConvertUTF8ToCP1251(j.at("Code")),
        ConvertUTF8ToCP1251(j.at("Name"))
    );
    int course = Speciality::MIN_COURSE;
    for (auto& disciplineList: j.at("Disciplines")) {
        speciality->GetDisciplineList(course) = disciplineList;
        course++;
    }
    for (auto& group : j.at("Groups")) {
        speciality->AddGroup(group);
    }
}

void from_json(const json& j, std::shared_ptr<Faculty>& faculty) {
    faculty = std::make_shared<Faculty>(
        ConvertUTF8ToCP1251(j.at("Name"))
    );
    for (auto& speciality : j.at("Specialities")) {
        faculty->AddSpeciality(speciality);
    }
}