#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "Logger.h"
#include "TestScript.h"
#include "TestShell.h"

#include "TestScenario/TestScenario.h"
#include "TestScenario/TestApp1.cpp"
#include "TestScenario/TestApp2.cpp"
#include "TestScenario/Write10AndCompare.cpp"
#include "TestScenario/Read10AndCompare.cpp"

using std::string;
using std::vector;

TestScript::TestScript() {
	// do nothing
}

TestScript* TestScript::testScript = nullptr;
TestScript* TestScript::getInstance()
{
	if (testScript == nullptr) {
		testScript = new TestScript();
	}

	return testScript;
}

bool TestScript::testScriptApp(string userInput) {
	vector<string> args = splitString(userInput);
	bool result = false;

	if (args[0] == "testapp1") {
		TestScenario* test = new TestApp1();
		result = test->runTest();
		delete test;
	}

	if (args[0] == "testapp2") {
		TestScenario* test = new TestApp2();
		result = test->runTest();
		delete test;
	}

	if (args[0] == "Write10AndCompare") {
		TestScenario* test = new Write10AndCompare();
		result = test->runTest();
		delete test;
	}

	if (args[0] == "Read10AndCompare") {
		TestScenario* test = new Read10AndCompare();
		result = test->runTest();
		delete test;
	}
	string strRes = (result == true) ? "PASS" : "FAIL";
	log(__func__, args[0] + "\t:" + strRes);

	return result;
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