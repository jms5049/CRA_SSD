#pragma once
#include <string>
#include "../TestShell.h"
#include "TestScenario.h"

using std::string;

class Write10AndCompare : public TestScenario {
public:
	Write10AndCompare() : TestScenario() {
		// do nothing
	}

	bool runTest() override {
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
};
