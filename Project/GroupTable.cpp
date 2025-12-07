#include "GroupTable.hpp"

#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <ranges>


GroupTable::GroupTable(std::shared_ptr<Group> group, bool includeOnlyFailing) {
    if (group == nullptr) {
        throw std::invalid_argument("Group cannot be nullptr");
    }
    m_group = group;
    m_includeOnlyFailing = includeOnlyFailing;
    m_sortColumn = nullptr;
    m_sortOrder = SortOrder::eAscending;
}

GroupTable::GroupTable(const GroupTable& other) {
    m_group = other.m_group;
    m_includeOnlyFailing = other.m_includeOnlyFailing;
    m_sortColumn = other.m_sortColumn;
    m_sortOrder = other.m_sortOrder;
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

    std::ranges::copy_if(m_group->GetStudents(),
        std::back_inserter(students),
        [&](auto& student) {
            return std::ranges::any_of(disciplines,
                [&](auto& discipline) {
                    const auto& res = student->GetSessionResults().GetResult(discipline);
                    return !m_includeOnlyFailing || res == nullptr || !res->IsPassed();
                }
            );
        }
    );

    auto getScoreOrZero = [](auto& student, auto& discipline) {
        const auto& res = student->GetSessionResults().GetResult(discipline);
        return res ? res->ToScore() : 0;
    };

    std::ranges::sort(students,
        [&](int a, int b) { return m_sortOrder == SortOrder::eAscending ? a < b : a > b; },
        [&](auto& student) {
            if (m_sortColumn != nullptr) {
                return getScoreOrZero(student, m_sortColumn);
            } else {
                return std::accumulate(disciplines.begin(), disciplines.end(), 0,
                    [&](int acc, auto& discipline) { return acc + getScoreOrZero(student, discipline); }
                );
            }
        }
    );

    for (auto& student : students) {
        tableBody.emplace_back();
        for (auto& discipline : disciplines) {
            tableBody.back().push_back(student->GetSessionResults().GetResult(discipline));
        }
    }

    return GroupTableData(std::move(students), std::move(disciplines), std::move(tableBody));
}
