#include <string>
#include <vector>
#include <typeinfo>
#include <iostream>

#include "../Logger.h"
#include "../TestShell.h"
#include "TestScenario.h"

TestScenario::TestScenario()
{
	testShell = TestShell::getInstance();
}

void TestScenario::log(string funcName, string strLog) {
	std::cout << "hi, this is TS " << std::endl;
	Logger* loggerTS = Logger::getInstance();
	string str = typeid(*this).name();
	str += ".";
	str += funcName;
	loggerTS->write(str, strLog);
}

string TestScenario::makeWriteCommand(int lba, string data)
{
	string result = "write ";
	result += to_string(lba);
	result += " " + data;
	return result;
}

string TestScenario::makeReadCommand(int lba)
{
	string result = "read ";
	result += to_string(lba);
	return result;
}

void TestScenario::writeRange(string data, int addrStart, int addrEnd) {
	string writeCommand;
	for (int addr = addrStart; addr < addrEnd; addr++) {
		testShell->executeCommand(makeWriteCommand(addr, data));
	}
}
