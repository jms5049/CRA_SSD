#pragma once
#include "SsdApi.h"
using namespace std;

class Logger;
class CommandFactory;
class ICommand;

class TestShell {
public:
	static TestShell* getInstance(Logger* logger);
	void executeCommand(string userInput);
	string getResult();

private:
	static TestShell* testShell;
	CommandFactory* commandFactory;
	ICommand* iCommand;
	Logger* logger;

	TestShell(Logger* logger);
	void inputParser(string userInput);
	vector<string> splitString(const string& str);
	void help_fullread();
};