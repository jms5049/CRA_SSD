#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Runner.h"
#include "Ssd.h"
#include "TestShell.h"
#include "TestScript.h"

using namespace std;

void Runner::runnerApp(string userInput) {
	vector<string> args = splitString(userInput);
	ifstream file(args[1]);
	TestShell* testShell = TestShell::getInstance();
	class TestScript testscript;

	if (!file.is_open()) {
		cerr << "Error: Failed to open " << args[1] << " file for reading!" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		bool result = false;
		cout << line << "\t\t" << "---   Run...";

		result = testscript.testScriptApp(line);

		if (result == true) 
			cout << "Pass" << endl;
		else {
			cout << "FAIL!" << endl;
			break;
		}

	}

	return;
}

vector<string> Runner::splitString(const string& str) {
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