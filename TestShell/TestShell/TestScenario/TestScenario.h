#pragma once

class TestScenario {
public:
	TestScenario();
	virtual bool runTest() = 0;

protected:
	TestShell* testShell;
	string name;

	string makeWriteCommand(int lba, string data);
	string makeReadCommand(int lba);
	void writeRange(string data, int addrStart, int addrEnd);

	void log(string funcName, string strLog);
};
