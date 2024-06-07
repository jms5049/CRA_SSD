#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "SsdApi.h"
#include "Ssd.h"
#include "TestShell.h"
#include "TestScript.h"
#include "Logger.h"

using std::string;


TestScript::TestScript(Logger* logger) {
	this->logger = logger;
}

TestScript* TestScript::testScript = nullptr;
TestScript* TestScript::getInstance(Logger* logger)
{
	if (testScript == nullptr) {
		testScript = new TestScript(logger);
	}

	return testScript;
}

void TestScript::testScriptApp(string userInput) {
	vector<string> args = splitString(userInput);
	if (args[0] == "testapp1") {
		printf("TestApp1 result: %s \n", (testApp1() == true) ? "PASS" : "FAIL");
	}
	if (args[0] == "testapp2") {
		printf("TestApp1 result: %s \n", (testApp2() == true) ? "PASS" : "FAIL");
	}
}

bool TestScript::testApp1() {
	string data = "0x5A5A5A5A";
	cout << "DEBUF#1\n";
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
	log(__func__);
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

void TestScript::log(string funcName) {
	Logger* loggerTS = Logger::getInstance();
	string str = typeid(*this).name();
	str += ".";
	str += funcName;
	loggerTS->write(str);
}