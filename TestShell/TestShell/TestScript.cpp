#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "Logger.h"
#include "Printer.h"
#include "TestScript.h"
#include "TestShell.h"

#include "TestScenario/TestScenario.h"
#include "TestScenario/TestApp1.h"
#include "TestScenario/TestApp2.h"
#include "TestScenario/Write10AndCompare.h"
#include "TestScenario/Read10AndCompare.h"

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

const vector<string> TestScript::supportedScenarios = {
	"testapp1",
	"testapp2",
	"Write10AndCompare",
	"Read10AndCompare",
};

bool TestScript::isSupportedTestScenario(string testScenarioName) {
	for (auto& curScenario : supportedScenarios) {
		if (testScenarioName == curScenario) return true;
	}

	return false;
}

bool TestScript::testScriptApp(string userInput) {
	vector<string> args = splitString(userInput);
	bool result = false;

	TestScenario* runningTest = getTestScenario(args[0]);
	
	if (runningTest != nullptr) {
		try {
			result = runningTest->runTest();
		}
		catch (exception e) {
			string printOut = "Error : ";
			printOut += e.what();
			Printer::getInstance()->print(printOut);
		}
		delete runningTest;
	}

	string strRes = (result == true) ? "PASS" : "FAIL";
	log(__func__, args[0] + "\t:" + strRes);

	return result;
}

TestScenario* TestScript::getTestScenario(const string& scenarioName)
{
	if (scenarioName == "testapp1") return new TestApp1();
	if (scenarioName == "testapp2") return new TestApp2();
	if (scenarioName == "Write10AndCompare") return new Write10AndCompare();
	if (scenarioName == "Read10AndCompare") return new Read10AndCompare();
	return nullptr;
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