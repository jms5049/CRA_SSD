#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "Logger.h"
#include "TestShell.h"
#include "TestScript.h"

using std::string;

TestScript::TestScript(TestShell* testShell) {
	this->testShell = testShell;
}

TestScript* TestScript::testScript = nullptr;
TestScript* TestScript::getInstance(TestShell* testShell)
{
	if (testScript == nullptr) {
		testScript = new TestScript(testShell);
	}

	return testScript;
}

bool TestScript::testScriptApp(string userInput) {
	vector<string> args = splitString(userInput);
	bool result = false;

	if (args[0] == "testapp1") {
		result = testApp1();
	}
	if (args[0] == "testapp2") {
		result = testApp2();
	}
	if (args[0] == "Write10AndCompare") {
		result = testWrite10AndCompare();
	}
	if (args[0] == "Read10AndCompare") {
		result = testRead10AndCompare();
	}
	string strRes = (result == true) ? "PASS" : "FAIL";
	log(__func__, args[0] + "\t:" + strRes);

	return result;
}

bool TestScript::testApp1() {
	string data = "0x5A5A5A5A";
	testShell->executeCommand("fullwrite " + data);
	testShell->executeCommand("fullread");
	for (int addr = 0; addr < 100; addr++) {
		testShell->executeCommand(makeReadCommand(addr));
		string result = testShell->getResult();
		if (result != data) {
			return false;
		}
	}
	return true;
}

bool TestScript::testApp2() {
	string data;
	data = "0xAAAABBBB";
	for (int cnt = 0; cnt < testCnt; cnt++) {
		writeAddrTest(data);
	}
	data = "0x12345678";
	writeAddrTest(data);

	for (int addr = 0; addr < testAddr; addr++) {
		testShell->executeCommand(makeReadCommand(addr));
		string result = testShell->getResult();
		if (result != data) {
			return false;
		}
	}
	return true;
}

void TestScript::writeAddrTest(string data) {
	string writeCommand;
	for (int addr = 0; addr < testAddr; addr++) {
		testShell->executeCommand(makeWriteCommand(addr, data));
	}
}



bool TestScript::testWrite10AndCompare() {
	string data;
	data = "0xAAAABBBB";

	for (int cnt = 0; cnt < 10; cnt++)
		testShell->executeCommand(makeWriteCommand(0, data));

	testShell->executeCommand(makeReadCommand(0));
	string result = testShell->getResult();

	if (result != data) return false;
	return true;
}

string TestScript::makeWriteCommand(int lba, string data)
{
	string result = "write ";
	result += to_string(lba);
	result += " " + data;
	return result;
}

string TestScript::makeReadCommand(int lba)
{
	string result = "read ";
	result += to_string(lba);
	return result;
}

bool TestScript::testRead10AndCompare() {
<<<<<<< HEAD
	log(__func__);
=======
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
	testShell->executeCommand(makeReadCommand(0));
	string data = testShell->getResult();
	string result;

	for (int cnt = 0; cnt < 10; cnt++) {
		testShell->executeCommand(makeReadCommand(0));
		result = testShell->getResult();

		if (result != data) return false;
	}

	return true;
}

vector<string> TestScript::splitString(const string& str) {
	istringstream iss(str);
	vector<string> tokens;
	string token;
	while (iss >> token) {
		if (!token.empty()) {
			tokens.push_back(token);
		}
	}
	return tokens;
}

void TestScript::log(string funcName, string strLog) {
	Logger* loggerTS = Logger::getInstance();
	string str = typeid(*this).name();
	str += ".";
	str += funcName;
	loggerTS->write(str, strLog);
}