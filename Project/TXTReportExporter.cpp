#include "TXTReportExporter.hpp"

#include <fstream>

std::vector<int> TXTReportExporter::CalculateColumnWidths(GroupTableData data) {
	std::vector<int> widths(data.GetDisciplines().size() + 2, 1);
	widths[0] = 3;
	for (Student* student : data.GetStudents()) {
		widths[0] = std::max(widths[0], (int)student->GetLastNameWithInitials().size());
	}
	for (int i = 1; i <= data.GetDisciplines().size(); i++) {
		widths[i] = 3;
	}
	widths.back() = 12;

	return widths;
}

std::string TXTReportExporter::TableSeparator(const std::vector<int>& widths) {
	std::string separator = "+";
	for (int width : widths) {
		separator.append(width + 2, '-');
		separator.push_back('+');
	}
	return separator;
}

std::string TXTReportExporter::TableRow(const std::vector<std::string>& cells, const std::vector<int>& widths) {
	std::string row = "|";
	for (int i = 0; i < widths.size(); i++) {
		row.append(" ");
		row.append(std::max(0, (int)(widths[i] - cells[i].size())), ' ');
		row.append(cells[i]);
		row.append(" |");
	}
	return row;
}

std::string TXTReportExporter::TableHeader(const GroupTableData& data, const std::vector<int>& widths) {
	std::vector<std::string> cells;
	cells.push_back("ФИО");
	for (int i = 1; i <= data.GetDisciplines().size(); i++) {
		cells.push_back(std::to_string(i));
	}
	cells.push_back("Средний балл");

	return TableRow(cells, widths);
}

std::vector<std::string> TXTReportExporter::TableBodyToStrings(const GroupTableData& data, const std::vector<int>& widths) {
	std::vector<std::string> result;

	std::vector<int> studentAverages = data.StudentAverages();
	for (int i = 0; i < data.GetStudents().size(); i++) {
		std::vector<std::string> cells(data.GetDisciplines().size() + 2);

		cells[0] = data.GetStudents()[i]->GetLastNameWithInitials();
		for (int j = 0; j < data.GetDisciplines().size(); j++) {
			AttestationResult* res = data.GetTableBody()[i][j];
			cells[j + 1] = res ? res->ToStringCompact() : "";
		}
		cells.back() = std::to_string(studentAverages[i]);

		result.push_back(TableRow(cells, widths));
	}

	return result;
}

std::string TXTReportExporter::TableDisciplineAverages(const GroupTableData& data, const std::vector<int>& widths) {
	std::vector<std::string> cells;
	cells.push_back("");
	for (int average : data.DisciplineAverages()) {
		cells.push_back(std::to_string(average));
	}
	cells.push_back(std::to_string(data.GroupAverage()));

	return TableRow(cells, widths);
}

void TXTReportExporter::Export(const GroupTable& groupTable, std::string filename) {
	GroupTableData data = groupTable.GetTableData();
	std::vector<int> widths = CalculateColumnWidths(data);
	std::string separator = TableSeparator(widths);

	std::ofstream fout(filename);

	if (!groupTable.GetIncludeOnlyFailing()) {
		fout << "Отчет об успеваемости студентов группы " << groupTable.GetGroup()->GetName() << std::endl;
	} else {
		fout << "Отчет о неуспевающих студентах группы " << groupTable.GetGroup()->GetName() << std::endl;
	}

	fout << std::endl;

	fout << separator << std::endl;
	fout << TableHeader(data, widths) << std::endl;
	fout << separator << std::endl;
	for (std::string row : TableBodyToStrings(data, widths)) {
		fout << row << std::endl;
	}
	fout << separator << std::endl;
	fout << TableDisciplineAverages(data, widths) << std::endl;
	fout << separator << std::endl;

	fout << std::endl;

	for (int i = 0; i < groupTable.GetDisciplineReferenceList().GetSize(); i++) {
		fout << (i+1) << " - " << groupTable.GetDisciplineReferenceList().GetDisciplineAt(i)->GetName() << std::endl;
	}
}
