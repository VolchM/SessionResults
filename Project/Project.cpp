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


    std::cout << "------- Статическая инициализация объектов -------" << std::endl;
    ExamResult res1(80);
    PassFailExamResult res2(false);
    std::cout << res1.ToString() << " " << res2.ToString() << std::endl;


    std::cout << "------- Динамическая инициализация объектов -------" << std::endl;
    ExamResult* res3 = new ExamResult(33);
    PassFailExamResult* res4 = new PassFailExamResult(true);

    std::cout << res3->ToString() << " " << res4->ToString() << std::endl;

    // Освобождение памяти
    delete res3;
    delete res4;


    std::cout << "------- Работа с объектами по ссылке -------" << std::endl;
    ExamResult& resRef = res1;
    std::cout << resRef.ToString() << std::endl;

    resRef = ExamResult(44); // Изменение объекта по ссылке
    std::cout << resRef.ToString() << " " << res1.ToString() << std::endl;


    std::cout << "------- Работа с объектами по указателю -------" << std::endl;
    ExamResult* resPtr = &res1;
    std::cout << resPtr->ToString() << std::endl;

    *resPtr = ExamResult(100); // Изменение объекта с помощью указателя
    std::cout << resPtr->ToString() << " " << res1.ToString() << std::endl;

    resPtr = new ExamResult(22); // Изменение указателя
    std::cout << resPtr->ToString() << " " << res1.ToString() << std::endl;

    delete resPtr; // Освобождение памяти


    std::cout << "------- Динамический массив объектов класса -------" << std::endl;
    const int arrSize1 = 3;
    ExamResult* resArray = new ExamResult[arrSize1] {33, 24, 55};
    for (int i = 0; i < arrSize1; i++) {
        std::cout << i << ": " << resArray[i].ToString() << std::endl;
    }
    delete[] resArray; // Освобождение памяти


    std::cout << "------- Массив динамических объектов класса -------" << std::endl;
    const int arrSize2 = 3;
    ExamResult* resPtrArray[arrSize2];
    resPtrArray[0] = new ExamResult(66);
    resPtrArray[1] = new ExamResult(44);
    resPtrArray[2] = new ExamResult(1);

    for (int i = 0; i < arrSize2; i++) {
        std::cout << i << ": " << resPtrArray[i]->ToString() << std::endl;
    }

    // Освобождение памяти
    for (int i = 0; i < arrSize2; i++) {
        delete resPtrArray[i];
    }


    std::cout << "------- Демонстрация работы других классов -------" << std::endl;

    // Динамическая инициализация объектов
    Speciality* pi = new Speciality("09.03.04", "Программная инженерия");
    pi->GetDisciplineList(2).AddDiscipline(new Discipline("Иностранный язык", Discipline::AttestationType::ePassFailExam));
    pi->GetDisciplineList(2).AddDiscipline(new Discipline("Программирование", Discipline::AttestationType::eExam));
    pi->GetDisciplineList(2).AddDiscipline(new Discipline("Архитектура ЭВМ", Discipline::AttestationType::eExam));

    Group* pi_43 = new Group(pi, "ПИ-43", 2);
    pi->AddGroup(pi_43);

    pi_43->AddStudent(new Student(pi_43, 12300325, "Иван", "Иванов", "Иванович"));
    pi_43->AddStudent(new Student(pi_43, 12300356, "Пётр", "Петров", "Петрович"));
    pi_43->AddStudent(new Student(pi_43, 12307377, "Сергей", "Сергеев", "Сергеевич"));
    pi_43->AddStudent(new Student(pi_43, 12303537, "Алексей", "Алексеев", "Алексеевич"));
    pi_43->AddStudent(new Student(pi_43, 12303890, "Дмитрий", "Дмитриев", "Дмитриевич"));
    

    srand(time(0));
    for (Student* student : pi_43->GetStudents()) {
        for (Discipline* discipline : pi->GetDisciplineList(pi_43->GetCourse()).GetDisciplines()) {
            if (discipline->GetAttestationType() == Discipline::AttestationType::eExam) {
                student->GetSessionResults().SetResult(discipline, new ExamResult(rand() % 101));
            } else {
                student->GetSessionResults().SetResult(discipline, new PassFailExamResult(rand() % 2));
            }
        }
    }

    std::cout << pi->GetCode() << " " << pi->GetName() << " " << pi->GetGroupAt(0)->GetName() << std::endl;

    for (int i = 0; i < pi->GetGroupAt(0)->GetStudentCount(); i++) {
        std::cout << (i+1) << ". " << pi->GetGroupAt(0)->GetStudentAt(i)->GetFullName() << std::endl;
    }
    

    GroupTable groupTable(pi_43);
    groupTable.SetDisciplineReferenceList(pi->GetDisciplineList(2).GetDisciplineReferenceList());
    
    groupTable.SortByDiscipline(groupTable.GetDisciplineReferenceList().GetDisciplineAt(1), GroupTable::SortOrder::eAscending);

    GroupTableData data = groupTable.GetTableData();
    std::cout << std::endl;
    for (int i = 0; i < data.GetStudents().size(); i++) {
        std::cout << data.GetStudents()[i]->GetLastNameWithInitials() << ": ";
        for (AttestationResult* cell : data.GetTableBody()[i]) {
            std::cout << (cell ? cell->ToString() : " ") << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Средний балл группы: " << data.GroupAverage() << std::endl;
    std::cout << std::endl;

    TXTReportExporter txtExporter;
    txtExporter.Export(groupTable, "report1.txt");
    std::cout << "Отчёт сохранён в report1.txt" << std::endl;

    groupTable.GetDisciplineReferenceList().RemoveDiscipline(pi->GetDisciplineList(2).GetDisciplines()[1]);
    groupTable.SortByAverage(GroupTable::SortOrder::eDescending);
    groupTable.SetIncludeOnlyFailing(true);

    txtExporter.Export(groupTable, "report2.txt");
    std::cout << "Отчёт сохранён в report2.txt" << std::endl;

    // Освобождение памяти
    delete pi;
}