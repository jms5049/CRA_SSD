#pragma once
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CommandFactory;
class ICommand;

class TestShell {
public:
	static TestShell* getInstance();
	void executeCommand(string userInput);
	string getResult();

private:
	static TestShell* testShell;
	CommandFactory* commandFactory;
	ICommand* iCommand;

	TestShell();
	void inputParser(string userInput);
	vector<string> splitString(const string& str);
};