#include <string>
#include <Windows.h>

#include "Ssd.h"

using std::string;

void Ssd::write(int lba, std::string data)
{
	// ex) 호출부 예시
	string writeCmd = "W " + std::to_string(lba);
	writeCmd += " " + data;
	ShellExecuteA(NULL, "open", "ssd", writeCmd.c_str(), "..\\..\\SSD\\", SW_HIDE);
}

int Ssd::read(int lba)
{
	return 0;
}
