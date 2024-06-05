#include <iostream>
#include <string>
#include <vector>

#include "SsdApi.h"
#include "Ssd.h"
#include "TestShell.h"
#include "TestScript.h"
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

int main() {
	class Ssd * ssd = new Ssd();
	class TestShell testShell(ssd);
	class TestScript testscript;

	while (1) {
		string input;
		cout << "cmd > ";

		getline(cin, input);

		if (isTestscript(input))
			testscript.testScriptApp(input);
		else if (isTestshell(input))
			testShell.inputParser(input);
		else
			cout << "INVALID COMMAND" << endl;
	}
}