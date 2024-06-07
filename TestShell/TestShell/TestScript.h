#pragma once
class TestScript {
public:
	static TestScript* getInstance(TestShell* testShell, Logger* logger);
	void testScriptApp(string userInput);

private:
	static TestScript* testScript;
	Logger* logger;
	TestShell* testShell;
	const int testCnt = 30;
	const int testAddr = 5;

	TestScript(TestShell* testShell, Logger* logger);
	vector<string> splitString(const string& str);

	bool testApp1();
	bool testApp2();
	void writeAddrTest(string data);

	bool testWrite10AndCompare();
	bool testRead10AndCompare();

	vector<string> splitString(const string& str);

	const int testCnt = 30;
	const int testAddr = 5;

	void log(string funcName);
};