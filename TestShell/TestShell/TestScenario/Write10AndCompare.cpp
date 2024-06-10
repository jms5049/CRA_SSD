#pragma once
#include <string>

#include "../TestShell.h"
#include "TestScenario.h"
#include "Write10AndCompare.h"

using std::string;

Write10AndCompare::Write10AndCompare() : TestScenario() {
	// do nothing
}

bool Write10AndCompare::runTest() {
	log("runTest", "TS_Start");
	string data;
	data = "0xAAAABBBB";
		
	for (int cnt = 0; cnt < 10; cnt++)
		testShell->executeCommand(makeWriteCommand(0, data));
		
	testShell->executeCommand(makeReadCommand(0));
	string result = testShell->getResult();
		
	if (result != data) return false;
	return true;
}
