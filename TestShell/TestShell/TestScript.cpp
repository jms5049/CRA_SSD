#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "Logger.h"
#include "TestShell.h"
#include "TestScript.h"

using std::string;

TestScript::TestScript(TestShell* testShell, Logger* logger) {
	this->testShell = testShell;
	this->logger = logger;
}

TestScript* TestScript::testScript = nullptr;
TestScript* TestScript::getInstance(TestShell* testShell, Logger* logger)
{
	if (testScript == nullptr) {
		testScript = new TestScript(testShell, logger);
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

	return result;
}

bool TestScript::testApp1() {
	string data = "0x5A5A5A5A";
	testShell->fullWrite(data);
	testShell->fullRead();
	for (int addr = 0; addr < 100; addr++) {
		string result = testShell->read(to_string(addr));
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
		testShell->read(to_string(addr));
		string result = testShell->read(to_string(addr));
		if (result != data) {
			return false;
		}
	}
	return true;
}

void TestScript::writeAddrTest(string data) {
	for (int addr = 0; addr < testAddr; addr++) {
		testShell->write(to_string(addr), data);
	}
}

bool TestScript::testWrite10AndCompare() {
	string data;
	data = "0xAAAABBBB";

	for (int cnt = 0; cnt < 10; cnt++)
		testShell->write(to_string(0), data);

	string result = testShell->read(to_string(0));

	if (result != data) return false;
	return true;
}

bool TestScript::testRead10AndCompare() {
	string data = testShell->read(to_string(0));
	string result;

	for (int cnt = 0; cnt < 10; cnt++) {
		result = testShell->read(to_string(0));

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