#pragma once
#include <string>
#include "../TestShell.h"
#include "TestScenario.h"

using std::string;

class TestApp2 : public TestScenario {
public:
	TestApp2() : TestScenario() {
		// do nothing
	}

	bool runTest() override {
		log("runTest", "TS_Start");
		const int testCnt = 30;
		const int testAddr = 5;
		string data;
		data = "0xAAAABBBB";
		for (int cnt = 0; cnt < testCnt; cnt++) {
			makeWriteCommand(testAddr, data);
		}
		data = "0x12345678";
		makeWriteCommand(testAddr, data);
		
		for (int addr = 0; addr < testAddr; addr++) {
			testShell->executeCommand(makeReadCommand(addr));
			string result = testShell->getResult();
			if (result != data) {
				return false;
			}
		}
		return true;
	}
};
