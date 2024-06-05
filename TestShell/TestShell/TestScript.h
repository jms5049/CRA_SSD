#pragma once
class TestScript {
public:
	TestScript();
	void testScriptApp(string userInput);

private:
	bool testApp1();
	bool testApp2();
	string readResult();
	string converAddrDataToString(int addr, string data);
	vector<string> splitString(const string& str);
	Ssd ssd;
	TestShell* testShell;
};