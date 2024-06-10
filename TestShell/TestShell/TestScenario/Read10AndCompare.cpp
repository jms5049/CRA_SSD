#pragma once
#include <string>
#include "../TestShell.h"
#include <typeinfo>

#include "TestScenario.h"

using std::string;

class Read10AndCompare : public TestScenario {
public:
	Read10AndCompare() : TestScenario() {
		// do nothing
	}

	bool runTest() override {
		log("runTest", "TS_Start");
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
};
