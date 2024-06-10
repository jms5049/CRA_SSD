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
	const int testAddrStart = 0;
	const int testAddrEnd = 5;
	string data;
	data = "0xAAAABBBB";
	for (int cnt = 0; cnt < testCnt; cnt++) {
		writeRange(data, testAddrStart, testAddrEnd);
	}

	data = "0x12345678";
	writeRange(data, testAddrStart, testAddrEnd);
		
	for (int addr = testAddrStart; addr < testAddrEnd; addr++) {
		testShell->executeCommand(makeReadCommand(addr));
		string result = testShell->getResult();
		if (result != data) {
			return false;
		}
	}
	return true;
}
