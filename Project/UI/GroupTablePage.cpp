#include "UI/GroupTablePage.hpp"

#include "GroupTable/ITextTableRenderer.hpp"
#include "GroupTable/StyledTextTableRenderer.hpp"
#include "GroupTable/OutlinedTextTableRenderer.hpp"
#include "GroupTable/TXTReportExporter.hpp"
#include "UI/MenuActionPicker.hpp"
#include "UI/ItemPicker.hpp"
#include "UI/QuickItemPicker.hpp"

#include <conio.h>
#include <format>
#include <iostream>
#include <set>
#include <sstream>
#include <algorithm>


GroupTablePage::GroupTablePage(std::shared_ptr<Faculty> faculty) {
	m_faculty = faculty;
}

void GroupTablePage::Start() {
	if (std::ranges::all_of(m_faculty->GetSpecialities(),
		[](auto& speciality) { return speciality->GetGroupCount() == 0; })) {
		std::cout << "В факультете отсутствуют группы\n";
		return;
	}

	GroupTable groupTable = CreateGroupTable();

	PrintTable(groupTable);

	std::cout << "Действия:\n";
	MenuActionPicker({
		{ "Экспорт отчёта в TXT файл", [&]() { ExportToTXT(groupTable); } },
		{ "Назад в главное меню", []() {} }
	}).PickAndRun();
}

GroupTable GroupTablePage::CreateGroupTable() {
	std::vector<std::string> specialityStrings;
	for (auto& speciality: m_faculty->GetSpecialities()) {
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


	std::cout << "Выберите дисциплины:\n";
	for (int i = 0; i < group->GetDisciplineList().GetSize(); i++) {
		std::cout << std::format("{}. {}\n", i + 1, group->GetDisciplineList().GetDisciplineAt(i)->ToString());
	}

	std::set<int> indices;
	bool readIndices = false;
	while (!readIndices) {
		indices.clear();
		readIndices = true;

		std::cout << "Введите номера дисциплин через запятую (например: 1,3,4): ";
		std::string input;
		std::getline(std::cin, input);

		std::stringstream ss(input);
		std::string nextNumber;
		while (std::getline(ss, nextNumber, ',')) {
			try {
				int value = std::stoi(nextNumber);
				if (value >= 1 && value <= group->GetDisciplineList().GetSize() && !indices.contains(value - 1)) {
					indices.insert(value - 1);
				} else {
					readIndices = false;
					std::cout << "Номера введены неверно\n";
					break;
				}
			} catch (std::invalid_argument) {
				readIndices = false;
				std::cout << "Номера введены неверно\n";
				break;
			} catch (std::out_of_range) {
				readIndices = false;
				std::cout << "Номера введены неверно\n";
				break;
			}
		}
	}

	DisciplineList disciplines;
	for (int index : indices) {
		disciplines.AddDiscipline(group->GetDisciplineList().GetDisciplineAt(index));
	}

	std::vector<std::string> sortOptions = { "Средний балл" };
	for (int i = 0; i < disciplines.GetSize(); i++) {
		sortOptions.push_back(disciplines.GetDisciplineAt(i)->ToString());
	}
	ItemPicker sortPicker(sortOptions);
	std::cout << "Выберите столбец для сортировки:\n";
	int sortSelection = sortPicker.Pick();

	QuickItemPicker sortOrderPicker({"По возрастанию", "По убыванию"});
	std::cout << "Выберите порядок сортировки:\n";
	GroupTable::SortOrder sortOrder = (sortOrderPicker.Pick() == 0) ? GroupTable::SortOrder::eAscending : GroupTable::SortOrder::eDescending;

	QuickItemPicker includeOnlyFailingPicker({"Включить всех студентов", "Включить только неуспевающих"});
	std::cout << "Выберите, включать ли всех студентов:\n";
	bool includeOnlyFailing = (includeOnlyFailingPicker.Pick() == 1);

	GroupTable groupTable(group, includeOnlyFailing);
	groupTable.SetDisciplineList(disciplines);

	if (sortSelection == 0) {
		groupTable.SortByAverage(sortOrder);
	} else {
		groupTable.SortByDiscipline(disciplines.GetDisciplineAt(sortSelection - 1), sortOrder);
	}

	return groupTable;
}

void GroupTablePage::PrintTable(const GroupTable& groupTable) {
	GroupTableData data = groupTable.GetTableData();

	std::cout << StyledTextTableRenderer::GetDefault()->RenderTable(data) << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < data.GetDisciplines().size(); i++) {
		std::cout << std::format("{} - {}\n", i + 1, data.GetDisciplines()[i]->GetName());
	}
}

void GroupTablePage::ExportToTXT(const GroupTable& groupTable) {
	auto [fileName, title, body, includeDate] = GetReportExportData(".txt");

	QuickItemPicker tableStylePicker({"Обычный", "С двойным контуром"});
	std::cout << "Выберите стиль таблицы:\n";
	int selectedTableStyle = tableStylePicker.Pick();

	std::cout << "Введите символ таблицы на пересечении (по умолчанию: +): ";
	char crossSymbol = _getch();
	if (crossSymbol == '\r') crossSymbol = '+';
	std::cout << std::endl;

	std::cout << "Введите горизонтальный символ таблицы (по умолчанию: -): ";
	char horizontalSymbol = _getch();
	if (horizontalSymbol == '\r') horizontalSymbol = '-';
	std::cout << std::endl;

	std::cout << "Введите вертикальный символ таблицы (по умолчанию: |): ";
	char verticalSymbol = _getch();
	if (verticalSymbol == '\r') verticalSymbol = '|';
	std::cout << std::endl;

	std::unique_ptr<ITextTableRenderer> renderer;
	if (selectedTableStyle == 0) {
		renderer = std::make_unique<StyledTextTableRenderer>(crossSymbol, horizontalSymbol, verticalSymbol);
	} else {
		renderer = std::make_unique<OutlinedTextTableRenderer>(crossSymbol, horizontalSymbol, verticalSymbol);
	}

	std::unique_ptr<IReportExporter> exporter = std::make_unique<TXTReportExporter>(fileName, std::move(renderer), title, body, includeDate);
	exporter->Export(groupTable);
	std::cout << std::format("Отчёт сохранён в {}\n", fileName);
}

std::tuple<std::string, std::string, std::string, bool> GroupTablePage::GetReportExportData(const std::string& fileExtension) {
	std::cout << "Введите имя файла для сохранения отчёта: ";
	std::string fileName;
	std::getline(std::cin, fileName);
	if (!fileName.ends_with(fileExtension)) {
		fileName += fileExtension;
	}

	std::cout << "Введите заголовок отчёта или пустую строку: ";
	std::string title;
	std::getline(std::cin, title);

	std::cout << "Введите текст отчёта или пустую строку: ";
	std::string body;
	std::getline(std::cin, body);

	QuickItemPicker includeDatePicker({"Не включать дату в отчёт", "Включать дату в отчёт"});
	std::cout << "Выберите, включать ли текущую дату в отчёт:\n";
	bool includeDate = (includeDatePicker.Pick() == 1);

	return { fileName, title, body, includeDate };
}