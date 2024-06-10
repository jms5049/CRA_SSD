#pragma once
#include <string>
#include "../TestShell.h"
#include "TestScenario.h"
#include "TestApp1.h"

using std::string;

TestApp1::TestApp1() : TestScenario() {
	// do nothing
}

bool TestApp1::runTest() {
	log("runTest", "TS_Start_TEST!!");
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