#include "FileReportExporter.hpp"

FileReportExporter::FileReportExporter(const std::string& filePath, const std::string& title, const std::string& body, bool includeDate){
	m_filePath = filePath;
	m_title = title;
	m_body = body;
	m_includeDate = includeDate;
}

FileReportExporter::FileReportExporter(const FileReportExporter& other) {
	m_filePath = other.m_filePath;
	m_title = other.m_title;
	m_body = other.m_body;
	m_includeDate = other.m_includeDate;
}

std::string FileReportExporter::GetFilePath() const {
	return m_filePath;
}

void FileReportExporter::SetFilePath(const std::string& value) {
	m_filePath = value;
}

std::string FileReportExporter::GetTitle() const {
	return m_title;
}

void FileReportExporter::SetTitle(const std::string& value) {
	m_title = value;
}

std::string FileReportExporter::GetBody() const {
	return m_body;
}

void FileReportExporter::SetBody(const std::string& value) {
	m_body = value;
}

bool FileReportExporter::GetIncludeDate() const {
	return m_includeDate;
}

void FileReportExporter::SetIncludeDate(bool value) {
	m_includeDate = value;
}
