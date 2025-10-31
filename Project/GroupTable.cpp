#include "GroupTable.hpp"

#include <stdexcept>
#include <algorithm>


GroupTable::GroupTable(Group* group, bool includeOnlyFailing) {
    if (group == nullptr) {
        throw std::invalid_argument("Group cannot be nullptr");
    }
    m_group = group;
    m_includeOnlyFailing = includeOnlyFailing;
    m_sortColumn = nullptr;
    m_sortOrder = SortOrder::eAscending;
}

Group* GroupTable::GetGroup() const {
    return m_group;
};

bool GroupTable::GetIncludeOnlyFailing() const {
    return m_includeOnlyFailing;
}

void GroupTable::SetIncludeOnlyFailing(bool value) {
    m_includeOnlyFailing = value;
}

const DisciplineReferenceList& GroupTable::GetDisciplineReferenceList() const {
    return m_disciplines;
}

DisciplineReferenceList& GroupTable::GetDisciplineReferenceList() {
    return m_disciplines;
}

void GroupTable::SetDisciplineReferenceList(const DisciplineReferenceList& disciplines) {
    m_disciplines = disciplines;
}

void GroupTable::SetDisciplineReferenceList(const std::vector<Discipline*>& disciplines) {
    m_disciplines = DisciplineReferenceList(disciplines);
}

void GroupTable::SortByDiscipline(Discipline* discipline, SortOrder sortOrder) {
    m_sortColumn = discipline;
    m_sortOrder = sortOrder;
}

void GroupTable::SortByAverage(SortOrder sortOrder) {
    m_sortColumn = nullptr;
    m_sortOrder = sortOrder;
}

GroupTableData GroupTable::GetTableData() const {
    std::vector<Student*> students;
    std::vector<Discipline*> disciplines;
    std::vector<std::vector<AttestationResult*>> tableBody;

    disciplines = m_disciplines.GetDisciplines();
    for (Student* student : m_group->GetStudents()) {
        for (Discipline* discipline : disciplines) {
            AttestationResult* res = student->GetSessionResults().GetResult(discipline);
            if (!m_includeOnlyFailing || res == nullptr || !res->IsPassed()) {
                students.push_back(student);
                break;
            }
        }
    }

    if (m_sortColumn != nullptr) {
        std::sort(students.begin(), students.end(), [&](Student* student1, Student* student2) {
            AttestationResult *res1, *res2;
            int percent1, percent2;

            res1 = student1->GetSessionResults().GetResult(m_sortColumn);
            res2 = student2->GetSessionResults().GetResult(m_sortColumn);
            percent1 = res1 ? res1->ToPercent() : 0;
            percent2 = res2 ? res2->ToPercent() : 0;

            return m_sortOrder == SortOrder::eAscending ? percent1 < percent2 : percent1 > percent2;
        });
    } else {
        std::sort(students.begin(), students.end(), [&](Student* student1, Student* student2) {
            AttestationResult *res1, *res2;
            int sum1 = 0, sum2 = 0;

            for (Discipline* discipline : disciplines) {
                res1 = student1->GetSessionResults().GetResult(discipline);
                res2 = student2->GetSessionResults().GetResult(discipline);
                sum1 += res1 ? res1->ToScore() : 0;
                sum2 += res2 ? res2->ToScore() : 0;
            }

            return m_sortOrder == SortOrder::eAscending ? sum1 < sum2 : sum1 > sum2;
        });
    }

    for (Student* student : students) {
        tableBody.emplace_back();
        for (Discipline* discipline : disciplines) {
            tableBody.back().push_back(student->GetSessionResults().GetResult(discipline));
        }
    }

    return GroupTableData(std::move(students), std::move(disciplines), std::move(tableBody));
}
