#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>

#include "Ssd.h"

using std::string;

const string Ssd::SSD_LOCATION = "..\\..\\SSD\\";

void Ssd::write(int lba, std::string data)
{
	string writeCmd = convertToWriteCmd(lba, data);
	executeSsdCmd(writeCmd);
}

string Ssd::read(int lba)
{
	string readCmd = convertToReadCmd(lba);
	executeSsdCmd(readCmd);
	return readResultFile("../../SSD/result.txt");
}

string Ssd::readResultFile(const std::string& filepath) {
	string content;
	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cerr << "Error: Failed to open result.txt file for reading!" << std::endl;
		return "";
	}

	std::string line;
	while (std::getline(file, line)) {
		content += line;
	}

	file.close();
	return content;
}

string Ssd::convertToReadCmd(int lba)
{
	string result = "R ";
	result += std::to_string(lba);
	result += " ";
	return result;
}

string Ssd::convertToWriteCmd(int lba, std::string& data)
{
	string result = "W ";
	result += std::to_string(lba);
	result += " ";
	result += data;
	return result;
}

void Ssd::executeSsdCmd(string& cmdOption) {
	SHELLEXECUTEINFOA sei;
	::ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));

	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.lpFile = "ssd.exe";
	sei.lpDirectory = SSD_LOCATION.c_str();
	sei.lpParameters = cmdOption.c_str();
	sei.nShow = SW_HIDE;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = "open";

	DWORD result = ShellExecuteExA(&sei);

	if (sei.hProcess != NULL)
	{
		// 프로세스 종료까지 대기
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
}