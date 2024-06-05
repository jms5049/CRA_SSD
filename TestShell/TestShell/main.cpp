#include <iostream>
#include <string>

#include "SsdApi.h"
#include "Ssd.h"
#include "TestShell.h"
#include "TestScript.h"
using namespace std;

bool isTestscript(string input) {
	if (input.find("testapp1") == 0 || input.find("testapp2") == 0)
		return true;
	return false;
}

bool isTestshell(string input) {
	if (input.find("read") == 0 || input.find("write") == 0 || input.find("exit") == 0 ||
		input.find("help") == 0 || input.find("fullwrite") == 0 || input.find("fullread") == 0)
		return true;
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
	}
}