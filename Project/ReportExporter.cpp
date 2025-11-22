#include "ReportExporter.hpp"

ReportExporter::ReportExporter(const std::string& filePath, const std::string& title, const std::string& body, bool includeDate){
	m_filePath = filePath;
	m_title = title;
	m_body = body;
	m_includeDate = includeDate;
}

ReportExporter::ReportExporter(const ReportExporter& other) {
	m_filePath = other.m_filePath;
	m_title = other.m_title;
	m_body = other.m_body;
	m_includeDate = other.m_includeDate;
}

std::string ReportExporter::GetFilePath() {
	return m_filePath;
}

void ReportExporter::SetFilePath(const std::string& value) {
	m_filePath = value;
}

std::string ReportExporter::GetTitle() {
	return m_title;
}

void ReportExporter::SetTitle(const std::string& value) {
	m_title = value;
}

std::string ReportExporter::GetBody() {
	return m_body;
}

void ReportExporter::SetBody(const std::string& value) {
	m_body = value;
}

bool ReportExporter::GetIncludeDate() {
	return m_includeDate;
}

void ReportExporter::SetIncludeDate(bool value) {
	m_includeDate = value;
}
