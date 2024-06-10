#pragma once
class TestScript {
public:
	static TestScript* getInstance(TestShell* testShell);
	bool testScriptApp(string userInput);

private:
	static TestScript* testScript;
	TestShell* testShell;
	const int testCnt = 30;
	const int testAddr = 5;

	TestScript(TestShell* testShell);
	vector<string> splitString(const string& str);

	bool testApp1();
	bool testApp2();
	void writeAddrTest(string data);

	bool testWrite10AndCompare();
	bool testRead10AndCompare();

<<<<<<< HEAD
	void log(string funcName);
=======
	void log(string funcName, string strLog);
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
	string makeWriteCommand(int lba, string data);
	string makeReadCommand(int lba);
};