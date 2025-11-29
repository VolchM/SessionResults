#include "Speciality.hpp"
#include "Discipline.hpp"
#include "Group.hpp"
#include "Student.hpp"
#include "ExamResult.hpp"
#include "PassFailExamResult.hpp"
#include "GroupTable.hpp"
#include "TXTReportExporter.hpp"
#include "StyledTXTReportExporter.hpp"
#include "OutlinedTXTReportExporter.hpp"

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
        for (const std::shared_ptr<Discipline>& discipline : pi_43->GetDisciplineList().GetDisciplines()) {
            if (discipline->GetAttestationType() == Discipline::AttestationType::eExam) {
                student->GetSessionResults().SetResult(discipline, std::make_shared<ExamResult>(rand() % 101));
            } else {
                student->GetSessionResults().SetResult(discipline, std::make_shared<PassFailExamResult>(rand() % 2));
            }
        }
    }

    GroupTable groupTable(pi_43);
    groupTable.SetDisciplineList(pi_43->GetDisciplineList());
    groupTable.SortByDiscipline(groupTable.GetDisciplineList().GetDisciplineAt(1), GroupTable::SortOrder::eAscending);

    std::unique_ptr<IReportExporter> exporter1 = std::make_unique<TXTReportExporter>("report1.txt", "Отчёт об успеваемости студентов группы ПИ-43");
    exporter1->Export(groupTable);
    std::cout << "Отчёт сохранён в report1.txt" << std::endl;

    groupTable.GetDisciplineList().RemoveDiscipline(pi->GetDisciplineList(2).GetDisciplines()[1]);
    groupTable.SortByAverage(GroupTable::SortOrder::eDescending);
    groupTable.SetIncludeOnlyFailing(true);

    std::unique_ptr<IReportExporter> exporter2 = std::make_unique<StyledTXTReportExporter>("report2.txt", TableStyle('0', '=', '|'), "Отчёт о неуспевающих студентах группы ПИ-43", "", true);
    exporter2->Export(groupTable);
    std::cout << "Отчёт сохранён в report2.txt" << std::endl;

    groupTable.GetDisciplineList().RemoveDisciplineAt(1);
    groupTable.GetDisciplineList().AddDiscipline(pi_43->GetDisciplineList().GetDisciplineAt(1));

    OutlinedTXTReportExporter exporter3("test.txt");
    // Присваивание объекта базового класса производному типу
    exporter3 = TXTReportExporter("report3.txt", "Отчёт о неуспевающих студентах группы ПИ-43", "", true);
    exporter3.Export(groupTable);
    std::cout << "Отчёт сохранён в report3.txt" << std::endl;
}
