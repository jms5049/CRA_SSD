#pragma once
class TestScript {
public:
	TestScript();
	void testScriptApp(string userInput);

private:
	Ssd ssd;
	TestShell* testShell;

	bool testApp1();
	bool testApp2();
	string readResult();
	void write5AddrTest(string data);

	string converAddrDataToString(int addr, string data);
	vector<string> splitString(const string& str);
};