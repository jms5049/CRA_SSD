#pragma once
#include "SsdApi.h"
using namespace std;

class CommandFactory;
class ICommand;

class TestShell {
public:
	static TestShell* getInstance();
	void executeCommand(string userInput);
	string getResult();
<<<<<<< HEAD
	bool isSupportedCommand(string command);
=======
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])

private:
	static TestShell* testShell;
	CommandFactory* commandFactory;
	ICommand* iCommand;

	TestShell();
	void inputParser(string userInput);
	vector<string> splitString(const string& str);
	void help_fullread();
};