#pragma once
#include <string>
#include "../TestShell.h"
#include "TestScenario.h"
#include "Read10AndCompare.h"

using std::string;

Read10AndCompare::Read10AndCompare() : TestScenario() {
	// do nothing
}

bool Read10AndCompare::runTest() {
	log("runTest", "TS_Start_Fixed");
	testShell->executeCommand(makeReadCommand(0));
	string data = testShell->getResult();
	string result;
		
	for (int cnt = 0; cnt < 10; cnt++) {
		testShell->executeCommand(makeReadCommand(0));
		result = testShell->getResult();
		
		if (result != data) return false;
	}
		
	return true;
}
