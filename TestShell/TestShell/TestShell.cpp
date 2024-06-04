#include <stdlib.h>
#include <string>
#include <regex>

#include "ShellException.h"
#include "SsdApi.h"
#include "TestShell.h"

using std::string;
using std::regex;
using std::regex_match;

TestShell::TestShell(SsdApi* ssdApi)
: ssdApi(ssdApi) {
	// do nothing
}

void TestShell::write(string input)
{
	int spacePos = input.find(' ');
	string strLba = input.substr(0, spacePos);
	string strData = input.substr(spacePos + 1, input.length());

	verifyWriteInput(spacePos, strLba, strData);

	int iLba = atoi(strLba.data());
	ssdApi->write(iLba, strData);
}

void TestShell::verifyWriteInput(int spacePos, std::string& strLba, std::string& strData)
{
	// 각 입력 위치와 길이 확인
	if (spacePos == string::npos || spacePos == 0) throw InvalidCommandException();
	if (strLba.length() > 2) throw InvalidCommandException();
	if (strData.length() > 10) throw InvalidCommandException();

	// LBA가 숫자로 입력됐는지 확인
	for (int i = 0; i < strLba.length(); i++) {
		if (strLba[i] < '0' || strLba[i] > '9') throw InvalidCommandException();
	}

	// data가 최대 16진수인지 확인
	if (strData[0] != '0' || strData[1] != 'x') throw InvalidCommandException();
	for (int i = 2; i < strData.length(); i++) {
		if (((strData[i] >= '0' && strData[i] <= '9')
			|| (strData[i] >= 'a' && strData[i] <= 'f')
			|| (strData[i] >= 'A' && strData[i] <= 'F')) == false)
		{
			throw InvalidCommandException();
		}
	}
}

void TestShell::exitApp() {
	exit(0);
}

void TestShell::help(string command) {
	if (command == "write") help_write();
	else if (command == "read") help_read();
	else if (command == "exit") help_exit();
	else if (command == "fullwrite") help_fullwrite();
	else if (command == "fullread") help_fullread();
	else {
		help_write();
		help_read();
		help_exit();
		help_fullwrite();
		help_fullread();
	}
}

void TestShell::help_write() {
	printf("write:\n\t write [address] [value] => write 3 0xaabbccdd\n");
}
void TestShell::help_read() {
	printf("read:\n\t read [address] => read 3 \n");
}
void TestShell::help_exit() {
	printf("exit:\n\t you can exit the program \n");
}
void TestShell::help_fullwrite() {
	printf("fullwrite:\n\t you can write overall region at once \n\t fullwrite [value] => fullwrite 0xabcdffff \n");
}
void TestShell::help_fullread() {
	printf("fullread:\n\t you can read overall region at once\n");
}
