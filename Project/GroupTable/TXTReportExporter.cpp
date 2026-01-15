#include "GroupTable/TXTReportExporter.hpp"

#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>


TXTReportExporter::TXTReportExporter(const std::string& filePath, std::unique_ptr<ITextTableRenderer> renderer, const std::string& title, const std::string& body, bool includeDate) :
	FileReportExporter(filePath, title, body, includeDate), m_renderer(std::move(renderer)) {}

TXTReportExporter::TXTReportExporter(const TXTReportExporter& other) :
	FileReportExporter(other) {}

void TXTReportExporter::Export(const GroupTable& groupTable) {
	GroupTableData data = groupTable.GetTableData();
	

	std::ofstream fout(m_filePath);

	if (!m_title.empty()) {
		fout << m_title << std::endl << std::endl;
	}
	if (!m_body.empty()) {
		fout << m_body << std::endl << std::endl;
	}
	if (m_includeDate) {
		time_t now = time(0);
		std::tm tmNow;
		localtime_s(&tmNow, &now);
		fout << "Дата генерации: " << std::put_time(&tmNow, "%d.%m.%Y") << std::endl << std::endl;
	}

	fout << m_renderer->RenderTable(data) << std::endl;
	fout << std::endl;

	for (int i = 0; i < data.GetDisciplines().size(); i++) {
		fout << (i+1) << " - " << data.GetDisciplines()[i]->GetName() << std::endl;
	}
}
