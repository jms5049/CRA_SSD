#pragma once
class TestScript {
public:
	TestScript();
	bool testScriptApp(string userInput);

private:
	TestShell* testShell;

	bool testApp1();
	bool testApp2();
	void writeAddrTest(string data);

	bool testWrite10AndCompare();
	bool testRead10AndCompare();

	string makeWriteCommand(int lba, string data);
	string makeReadCommand(int lba);

	vector<string> splitString(const string& str);

	const int testCnt = 30;
	const int testAddr = 5;
};