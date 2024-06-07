#include <iostream>
#include <string>
#include <vector>

#include "TestShell.h"
#include "TestScript.h"
#include "Runner.h"
using namespace std;

bool isTestscript(string input) {
	vector<string> testScriptCmds = { "testapp1", "testapp2" };
	for (auto& cmd : testScriptCmds) {
		if (input.find(cmd) == 0) return true;
	}
	return false;
}

bool isTestshell(string input) {
	vector<string> testShellCmds = { "read", "write", "exit", "help", "fullwrite", "fullread" };
	for (auto& cmd : testShellCmds) {
		if (input.find(cmd) == 0) return true;
	}
	return false;
}

bool isRunner(string input) {
	vector<string> runnerCmds = { "runner" };
	for (auto& cmd : runnerCmds) {
		if (input.find(cmd) == 0) return true;
	}
	return false;
}

int main() {
	TestShell* testShell = TestShell::getInstance();
	TestScript testscript;
	Runner testRunner;

	while (1) {
		string input;
		cout << "cmd > ";

		getline(cin, input);

		try {
			if (isTestscript(input))
				testscript.testScriptApp(input);
			else if (isTestshell(input))
				testShell->executeCommand(input);
			else if (isRunner(input))
				testRunner.runnerApp(input);
			else
				cout << "INVALID COMMAND : NOT supported Command." << endl;
		}
		catch (exception e) {
			cout << "INVALID COMMAND : " << e.what() << endl;
		}
	}
}