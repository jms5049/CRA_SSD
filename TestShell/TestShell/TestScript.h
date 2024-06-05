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
	void write5AddrTest(string data);

	vector<string> splitString(const string& str);
};