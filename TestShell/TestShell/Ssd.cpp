#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>

#include "Ssd.h"
#include "SsdApi.h"
#include "Logger.h"
#include "Printer.h"

using std::string;

#if _DEBUG
const string Ssd::ssdLocation = "..\\..\\SSD\\";
const string Ssd::ssdResultFile = "../../SSD/result.txt";
#else
const string Ssd::ssdLocation = ".\\";
const string Ssd::ssdResultFile = "./SSD/result.txt";
#endif

Ssd::Ssd(){
}

Ssd* Ssd::ssd = nullptr;
Ssd* Ssd::getInstance() {
	if (ssd == nullptr) {
		ssd = new Ssd();
	}

	return ssd;
}

void Ssd::write(int lba, std::string data)
{
	string writeCmd = convertToWriteCmd(lba, data);
	executeSsdCmd(writeCmd);
}

string Ssd::read(int lba)
{
	string readCmd = convertToReadCmd(lba);
	executeSsdCmd(readCmd);
	return readResultFile(ssdResultFile);
}

void Ssd::erase(int lba, int size) {
	string eraseCmd = convertToEraseCmd(lba, size);
	executeSsdCmd(eraseCmd);
}

void Ssd::flush()
{
	string flushCmd = "F";
	executeSsdCmd(flushCmd);
}

string Ssd::readResultFile(const std::string& filepath) {
	string content;
	std::ifstream file(filepath);
	if (!file.is_open()) {
		string printOut = "Error: Failed to open result.txt file for reading!\n";
		Printer::getInstance()->print(printOut);
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

string Ssd::convertToEraseCmd(int lba, int size)
{
	string result = "E ";
	result += std::to_string(lba);
	result += " ";
	result += std::to_string(size);
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
	sei.lpDirectory = ssdLocation.c_str();
	sei.lpParameters = cmdOption.c_str();
	sei.nShow = SW_HIDE;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = "open";

	DWORD result = ShellExecuteExA(&sei);
	log(__func__, cmdOption.c_str());

	if (sei.hProcess != NULL)
	{
		// 프로세스 종료까지 대기
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
}

void Ssd::log(string funcName, string logStr) {
	Logger* logger = Logger::getInstance();
	string strLog = "[SSD]--------------------------------------------";
	strLog += logStr;
	logger->write(funcName, strLog);
}