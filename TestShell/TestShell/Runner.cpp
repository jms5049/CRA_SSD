#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Runner.h"
#include "Ssd.h"
#include "Logger.h"
#include "TestShell.h"
#include "TestScript.h"

using namespace std;

void Runner::runnerApp(string filename) {
	ifstream file(filename);
	Logger* logger = Logger::getInstance();
	TestShell* testShell = TestShell::getInstance();
	TestScript* testScript = TestScript::getInstance();

	if (!file.is_open()) {
		cerr << "Error: Failed to open " << filename << " file for reading!" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		bool result = false;
		cout << line << "\t\t" << "---   Run...";

		result = testScript->testScriptApp(line);

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