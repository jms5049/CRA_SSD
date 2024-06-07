#include <iostream>
#include <string>
#include <vector>

#include "Logger.h"
#include "TestShell.h"
#include "TestScript.h"
#include "Runner.h"
using namespace std;

bool isTestscript(string input) {
	vector<string> testScriptCmds = { "testapp1", "testapp2" , "Write10AndCompare", "Read10AndCompare" };
	for (auto& cmd : testScriptCmds) {
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
	Logger* logger = Logger::getInstance();
	TestShell* testShell = TestShell::getInstance(logger);
	TestScript* testScript = TestScript::getInstance(testShell, logger);
	Runner testRunner;

	while (1) {
		string input;
		cout << "cmd > ";

		getline(cin, input);

		try {
			if (isTestscript(input))
				testScript->testScriptApp(input);
			else if (testShell->isSupportedCommand(input))
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