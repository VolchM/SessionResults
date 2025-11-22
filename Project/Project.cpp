#include "Speciality.hpp"
#include "Discipline.hpp"
#include "Group.hpp"
#include "Student.hpp"
#include "ExamResult.hpp"
#include "PassFailExamResult.hpp"
#include "GroupTable.hpp"
#include "TXTReportExporter.hpp"

#include <iostream>


int main() {
    setlocale(LC_ALL, "Rus");

    std::cout << "------- Демонстрация работы программы -------" << std::endl;

    // Инициализация объектов
    std::shared_ptr<Speciality> pi = std::make_shared<Speciality>("09.03.04", "Программная инженерия");
    pi->GetDisciplineList(2).AddDiscipline(std::make_shared<Discipline>("Иностранный язык", Discipline::AttestationType::ePassFailExam));
    pi->GetDisciplineList(2).AddDiscipline(std::make_shared<Discipline>("Программирование", Discipline::AttestationType::eExam));
    pi->GetDisciplineList(2).AddDiscipline(std::make_shared<Discipline>("Архитектура ЭВМ", Discipline::AttestationType::eExam));

    std::shared_ptr<Group> pi_43 = std::make_shared<Group>("ПИ-43", 2);
    pi->AddGroup(pi_43);

    pi_43->AddStudent(std::make_shared<Student>(12300325, "Иван", "Иванов", "Иванович"));
    pi_43->AddStudent(std::make_shared<Student>(12300356, "Пётр", "Петров", "Петрович"));
    pi_43->AddStudent(std::make_shared<Student>(12307377, "Сергей", "Сергеев", "Сергеевич"));
    pi_43->AddStudent(std::make_shared<Student>(12303537, "Алексей", "Алексеев", "Алексеевич"));
    pi_43->AddStudent(std::make_shared<Student>(12303890, "Дмитрий", "Дмитриев", "Дмитриевич"));
    

    srand(13);
    for (const std::shared_ptr<Student>& student : pi_43->GetStudents()) {
        for (const std::shared_ptr<Discipline>& discipline : pi->GetDisciplineList(pi_43->GetCourse()).GetDisciplines()) {
            if (discipline->GetAttestationType() == Discipline::AttestationType::eExam) {
                student->GetSessionResults().SetResult(discipline, std::make_shared<ExamResult>(rand() % 101));
            } else {
                student->GetSessionResults().SetResult(discipline, std::make_shared<PassFailExamResult>(rand() % 2));
            }
        }
    }

    std::cout << pi->GetCode() << " " << pi->GetName() << " " << pi->GetGroupAt(0)->GetName() << std::endl;

    for (int i = 0; i < pi->GetGroupAt(0)->GetStudentCount(); i++) {
        std::cout << (i+1) << ". " << pi->GetGroupAt(0)->GetStudentAt(i)->GetFullName() << std::endl;
    }
    

    GroupTable groupTable(pi_43);
    groupTable.SetDisciplineList(pi->GetDisciplineList(2));
    
    groupTable.SortByDiscipline(groupTable.GetDisciplineList().GetDisciplineAt(1), GroupTable::SortOrder::eAscending);

    GroupTableData data = groupTable.GetTableData();
    std::cout << std::endl;
    for (int i = 0; i < data.GetStudents().size(); i++) {
        std::cout << data.GetStudents()[i]->GetLastNameWithInitials() << ": ";
        for (auto& cell : data.GetTableBody()[i]) {
            if (cell) {
                std::cout << *cell;
            } else {
                std::cout << " ";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Средний балл группы: " << data.GroupAverage() << std::endl;
    std::cout << std::endl;


    std::unique_ptr<ReportExporter> exporter = std::make_unique<TXTReportExporter>("report1.txt", "Отчёт об успеваемости студентов группы ПИ-43");

    exporter->Export(groupTable);
    std::cout << "Отчёт сохранён в report1.txt" << std::endl;

    groupTable.GetDisciplineList().RemoveDiscipline(pi->GetDisciplineList(2).GetDisciplines()[1]);
    groupTable.SortByAverage(GroupTable::SortOrder::eDescending);
    groupTable.SetIncludeOnlyFailing(true);

    exporter->SetFilePath("report2.txt");
    exporter->SetTitle("Отчёт о неуспевающих студентах группы ПИ-43");
    exporter->SetIncludeDate(true);
    exporter->Export(groupTable);
    std::cout << "Отчёт сохранён в report2.txt" << std::endl;
}
