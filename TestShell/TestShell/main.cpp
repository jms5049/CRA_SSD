#include <iostream>
#include <string>
#include <vector>
#include <io.h>

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

bool isRunner(int argc, char* argv[]) {
	if (argc != 2) return false;
	if (access(argv[1], 0) == -1) return false;
	return true;
}

int main(int argc, char* argv[]) {
	Logger* logger = Logger::getInstance();
	TestShell* testShell = TestShell::getInstance();
	TestScript* testScript = TestScript::getInstance(testShell);
	Runner testRunner;

	if (isRunner(argc, argv)) {
		testRunner.runnerApp(argv[1]);	// argv[1] 은 runner 파일명.
	}
	else {
		while (1) {
			string input;
			cout << "cmd > ";

			getline(cin, input);

<<<<<<< HEAD
			try {
				if (isTestscript(input))
					testScript->testScriptApp(input);
				else if (testShell->isSupportedCommand(input))
					testShell->executeCommand(input);
				else
					cout << "INVALID COMMAND : NOT supported Command." << endl;
			}
			catch (exception e) {
				cout << "INVALID COMMAND : " << e.what() << endl;
			}
=======
		try {
			if (isTestscript(input))
				testScript->testScriptApp(input);
			else if (isTestshell(input))
				testShell->executeCommand(input);
			else if (isRunner(input))
				testRunner.runnerApp(input);
			else
				cout << "INVALID COMMAND : NOT supported Command." << endl;
		}
		catch (exception e) {
			cout << "INVALID COMMAND : " << e.what() << endl;
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])
		}
	}
}