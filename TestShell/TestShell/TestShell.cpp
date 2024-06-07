#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <exception>

#include "Logger.h"
#include "TestShell.h"
#include "Command/ICommand.h"
#include "Command/CommandFactory.h"

using std::string;
using std::regex;
using std::regex_match;

TestShell::TestShell(Logger* logger) {
	this->logger = logger;
	commandFactory = CommandFactory::getCommandFactory();
}

TestShell* TestShell::testShell = nullptr;
TestShell* TestShell::getInstance(Logger* logger)
{
	if (testShell == nullptr) {
		testShell = new TestShell(logger);
	}

	return testShell;
}

void TestShell::executeCommand(string userInput) {
	inputParser(userInput);
	iCommand->verifyOptions();
	iCommand->execute();
}

string TestShell::getResult() {
	return iCommand->getResult();
}

bool TestShell::isSupportedCommand(string command)
{
	return commandFactory->isSupportedCommand(command);
}

void TestShell::inputParser(string userInput) {
	vector<string> args = splitString(userInput);

	iCommand = commandFactory->getCommand(args);
	if (iCommand == nullptr) throw std::invalid_argument("NOT supported Command.");
}

vector<string> TestShell::splitString(const string& str) {
	istringstream iss(str);
	vector<string> tokens;
	string token;
	while (iss >> token) {
		if (!token.empty()) {
			tokens.push_back(token);
		}
	}
	return tokens;
}
