#pragma once
using namespace std;

class TestScenario;

class TestScript {
public:
	static TestScript* getInstance();
	bool isSupportedTestScenario(string testScenarioName);
	bool testScriptApp(string userInput);

private:
	static TestScript* testScript;
	static const vector<string> supportedScenarios;

	TestScript();
	vector<string> splitString(const string& str);
	TestScenario* getTestScenario(const string& scenarioName);

	void log(string funcName, string strLog);
};