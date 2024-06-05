#include <string>
#include <iostream>
#include <Windows.h>

#include "Ssd.h"

using std::string;

const LPCSTR Ssd::SSD_LOCATION = "..\\..\\SSD\\";

void Ssd::write(int lba, std::string data)
{
	string writeCmd = convertToWriteCmd(lba, data);
	ShellExecuteA(NULL, "open", "ssd", writeCmd.c_str(), SSD_LOCATION, SW_HIDE);
}

string Ssd::convertToWriteCmd(int lba, std::string& data)
{
	string result = "W ";
	result += std::to_string(lba);
	result += " ";
	result += data;
	return result;
}

int Ssd::read(int lba)
{
	return 0;
}
