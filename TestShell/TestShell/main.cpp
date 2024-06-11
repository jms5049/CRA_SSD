#include <iostream>
#include <string>
#include <vector>
#include <io.h>

#include "Logger.h"
#include "TestShell.h"
#include "TestScript.h"
#include "Runner.h"
#include "Printer.h"

using namespace std;

bool isRunner(int argc, char* argv[]) {
	if (argc != 2) return false;
	if (access(argv[1], 0) == -1) return false;
	return true;
}

int main(int argc, char* argv[]) {
	Logger* logger = Logger::getInstance();
	TestShell* testShell = TestShell::getInstance();
	TestScript* testScript = TestScript::getInstance();
	Runner testRunner;

	if (isRunner(argc, argv)) {
		Printer::getInstance()->setIsRunner(true);
		testRunner.runnerApp(argv[1]);	// argv[1] 은 runner 파일명.
	}
	else {
		while (1) {
			string input;
			cout << "cmd > ";

			getline(cin, input);

			try {
				if (testScript->isSupportedTestScenario(input))
					testScript->testScriptApp(input);
				else if (testShell->isSupportedCommand(input))
					testShell->executeCommand(input);
				else
					cout << "INVALID COMMAND : NOT supported Command." << endl;
			}
			catch (exception e) {
				cout << "INVALID COMMAND : " << e.what() << endl;
			}
		}
	}
}