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
	ShellExecuteA(NULL, "open", "ssd", writeCmd.c_str(), SSD_LOCATION.c_str(), SW_HIDE);
}

string Ssd::convertToWriteCmd(int lba, std::string& data)
{
	string result = "W ";
	result += std::to_string(lba);
	result += " ";
	result += data;
	return result;
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
		content += line + "\n";
	}

	file.close();
	return content;
}

string Ssd::read(int lba)
{
	string readCmd = convertToReadCmd(lba);
	ShellExecuteA(NULL, "open", "ssd", readCmd.c_str(), SSD_LOCATION.c_str(), SW_HIDE);
	return readResultFile("../../SSD/result.txt");
}

string Ssd::convertToReadCmd(int lba)
{
	string result = "R ";
	result += std::to_string(lba);
	result += " ";
	return result;
}