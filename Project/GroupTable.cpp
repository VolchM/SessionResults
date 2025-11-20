#include "GroupTable.hpp"

#include <stdexcept>
#include <algorithm>


GroupTable::GroupTable(std::shared_ptr<Group> group, bool includeOnlyFailing) {
    if (group == nullptr) {
        throw std::invalid_argument("Group cannot be nullptr");
    }
    m_group = group;
    m_includeOnlyFailing = includeOnlyFailing;
    m_sortColumn = nullptr;
    m_sortOrder = SortOrder::eAscending;
}

std::shared_ptr<Group> GroupTable::GetGroup() const {
    return m_group;
};

bool GroupTable::GetIncludeOnlyFailing() const {
    return m_includeOnlyFailing;
}

void GroupTable::SetIncludeOnlyFailing(bool value) {
    m_includeOnlyFailing = value;
}

const DisciplineList& GroupTable::GetDisciplineList() const {
    return m_disciplines;
}

DisciplineList& GroupTable::GetDisciplineList() {
    return m_disciplines;
}

void GroupTable::SetDisciplineList(const DisciplineList& disciplines) {
    m_disciplines = disciplines;
}

void GroupTable::SetDisciplineList(const std::vector<std::shared_ptr<Discipline>>& disciplines) {
    m_disciplines = DisciplineList(disciplines);
}

void GroupTable::SortByDiscipline(std::shared_ptr<Discipline> discipline, SortOrder sortOrder) {
    m_sortColumn = discipline;
    m_sortOrder = sortOrder;
}

void GroupTable::SortByAverage(SortOrder sortOrder) {
    m_sortColumn = nullptr;
    m_sortOrder = sortOrder;
}

GroupTableData GroupTable::GetTableData() const {
    GroupTableData::StudentArray students;
    GroupTableData::DisciplineArray disciplines;
    GroupTableData::AttestationResultTable tableBody;

    disciplines = m_disciplines.GetDisciplines();
    for (auto& student : m_group->GetStudents()) {
        for (auto& discipline : disciplines) {
            const std::shared_ptr<AttestationResult>& res = student->GetSessionResults().GetResult(discipline);
            if (!m_includeOnlyFailing || res == nullptr || !res->IsPassed()) {
                students.push_back(student);
                break;
            }
        }
    }

    if (m_sortColumn != nullptr) {
        std::sort(students.begin(), students.end(), [&](auto& student1, auto& student2) {
            const std::shared_ptr<AttestationResult> &res1 = student1->GetSessionResults().GetResult(m_sortColumn);
            const std::shared_ptr<AttestationResult> &res2 = student2->GetSessionResults().GetResult(m_sortColumn);

            int score1 = res1 ? res1->ToScore() : 0;
            int score2 = res2 ? res2->ToScore() : 0;

            return m_sortOrder == SortOrder::eAscending ? score1 < score2 : score1 > score2;
        });
    } else {
        std::sort(students.begin(), students.end(), [&](auto& student1, auto& student2) {
            int sum1 = 0, sum2 = 0;

            for (auto& discipline : disciplines) {
                const std::shared_ptr<AttestationResult>& res1 = student1->GetSessionResults().GetResult(discipline);
                const std::shared_ptr<AttestationResult>& res2 = student2->GetSessionResults().GetResult(discipline);
                sum1 += res1 ? res1->ToScore() : 0;
                sum2 += res2 ? res2->ToScore() : 0;
            }

            return m_sortOrder == SortOrder::eAscending ? sum1 < sum2 : sum1 > sum2;
        });
    }

    for (auto& student : students) {
        tableBody.emplace_back();
        for (auto& discipline : disciplines) {
            tableBody.back().push_back(student->GetSessionResults().GetResult(discipline));
        }
    }

    return GroupTableData(std::move(students), std::move(disciplines), std::move(tableBody));
}
