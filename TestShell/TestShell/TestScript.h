#pragma once
using namespace std;

class TestScript {
public:
	static TestScript* getInstance();
	bool testScriptApp(string userInput);

private:
	static TestScript* testScript;

	TestScript();
	vector<string> splitString(const string& str);

	void log(string funcName, string strLog);
};