#pragma once
#include <string>
#include "../TestShell.h"
#include "TestScenario.h"
#include "TestApp2.h"

using std::string;

TestApp2::TestApp2() : TestScenario() {
	// do nothing
}

bool TestApp2::runTest() {
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
