#include "UI/ResultsSelectPage.hpp"

#include "UI/ItemPicker.hpp"

#include <iostream>
#include <vector>
#include <algorithm>


ResultsSelectPage::ResultsSelectPage(std::shared_ptr<Faculty> faculty) {
	m_faculty = faculty;
}

void ResultsSelectPage::Start() {
	if (std::ranges::all_of(m_faculty->GetSpecialities(),
		[](auto& speciality) { return speciality->GetGroupCount() == 0; })) {
		std::cout << "В факультете отсутствуют группы\n";
		return;
	}

	std::vector<std::string> specialityStrings;
	for (auto& speciality : m_faculty->GetSpecialities()) {
		if (speciality->GetGroupCount() != 0) {
			specialityStrings.push_back(speciality->ToString());
		}
	}
	ItemPicker specialityPicker(specialityStrings);

	std::cout << "Выберите специальность:\n";
	std::shared_ptr<Speciality> speciality = m_faculty->GetSpecialityAt(specialityPicker.Pick());


	std::vector<std::string> groupStrings;
	for (auto& group: speciality->GetGroups()) {
		groupStrings.push_back(group->ToString());
	}
	ItemPicker groupPicker(groupStrings);

	std::cout << "Выберите группу:\n";
	std::shared_ptr<Group> group = speciality->GetGroupAt(groupPicker.Pick());


	std::vector<std::string> disciplineStrings;
	for (auto& discipline : group->GetDisciplineList().GetDisciplines()) {
		disciplineStrings.push_back(discipline->ToString());
	}
	ItemPicker disciplinePicker(disciplineStrings);

	std::cout << "Выберите дисциплину:\n";
	std::shared_ptr<Discipline> discipline = group->GetDisciplineList().GetDisciplineAt(disciplinePicker.Pick());

	ResultsEditingPage(group, discipline).Start();
}
