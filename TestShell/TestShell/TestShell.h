#pragma once
#include <vector>
#include <string>

#include "SsdApi.h"
using namespace std;

class CommandFactory;
class ICommand;

class TestShell {
public:
	static TestShell* getInstance();
	void executeCommand(string userInput);
	string getResult();
	bool isSupportedCommand(string command);

private:
	static TestShell* testShell;
	CommandFactory* commandFactory;
	ICommand* iCommand = nullptr;

	TestShell();
	void inputParser(string userInput);
	vector<string> splitString(const string& str);
};