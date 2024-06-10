#pragma once
#include <string>
#include "../TestShell.h"
#include "TestScenario.h"

using std::string;

class TestApp1 : public TestScenario {
public:
	TestApp1() : TestScenario() {
		// do nothing
	}

	bool runTest() override {
		string data = "0x5A5A5A5A";
		testShell->executeCommand("fullwrite " + data);
		testShell->executeCommand("fullread");
		for (int addr = 0; addr < 100; addr++) {
			testShell->executeCommand(makeReadCommand(addr));
			string result = testShell->getResult();
			if (result != data) {
				return false;
			}
		}
		return true;
	}
};
