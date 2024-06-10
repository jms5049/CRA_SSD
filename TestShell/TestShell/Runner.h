#pragma once
#include <string>
using namespace std;

class Runner {
public:
	Runner() {};
	void RunnerApp(string userInput);

private:
	string scriptFileName;
	vector<string> splitString(const string& str);
};