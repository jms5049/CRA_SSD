#include <string>
#include <Windows.h>

#include "Ssd.h"

using std::string;

void Ssd::write(int lba, std::string data)
{
	// ex) ȣ��� ����
	// string writeCmd = lba + " " + data;
	// ShellExecuteA(NULL, "open", "ssd.exe", writeCmd.c_str(), NULL, SW_SHOW);
}

int Ssd::read(int lba)
{
	return 0;
}
