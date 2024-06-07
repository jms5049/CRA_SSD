#pragma once
class TestScript {
public:
	static TestScript* getInstance(Logger* logger);
	void testScriptApp(string userInput);

private:
	static TestScript* testScript;
	Logger* logger;
	TestShell* testShell;

	bool testApp1();
	bool testApp2();
	void writeAddrTest(string data);

	TestScript(Logger* logger);
	vector<string> splitString(const string& str);

	const int testCnt = 30;
	const int testAddr = 5;

	void log(string funcName);
};