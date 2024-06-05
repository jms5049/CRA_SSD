#include <string>
#include <fstream>

#include "SsdApi.h"
#include "Ssd.h"
#include "TestShell.h"
#include "TestScript.h"

using std::string;

TestScript::TestScript() {
	testShell = new TestShell(&ssd);
}

bool TestScript::testApp1() {
	string data = "0x5a5a5a5a";
	testShell->fullWrite(data);
	testShell->fullRead();
	string result = readResult();
	if (result != data) {
		return false;
	}
	return true;
}

bool TestScript::testApp2() {
	string data;
	data = "0xAAAABBBB";
	for (int cnt = 0; cnt < 30; cnt++) {
		write5AddrTest(data);
	}

	data = "0x12345678";
	write5AddrTest(data);

	for (int addr = 0; addr < 5; addr++) {
		testShell->read(to_string(addr));
		string result = readResult();
		if (result != data) {
			return false;
		}
	}
	return true;
}

void TestScript::write5AddrTest(string data) {
	for (int addr = 0; addr < 5; addr++) {
		testShell->write(to_string(addr), data);
	}
}

string TestScript::readResult()
{
	string filepath = "../../SSD/result.txt";
	std::ifstream file(filepath);

	string line = "";
	if (file.is_open()) {
		getline(file, line);
		file.close();
	}

	return line;
}

void TestScript::testScriptApp(string userInput) {
	vector<string> args = splitString(userInput);
	if (args[0] == "testapp1") {
		printf("TestApp1 result: %d \n", testApp1());
	}
	if (args[0] == "testapp2") {
		printf("TestApp1 result: %d \n", testApp2());
	}
}

vector<string> TestScript::splitString(const string& str) {
	istringstream iss(str);
	vector<string> tokens;
	string token;
	while (iss >> token) {
		if (!token.empty()) {
			tokens.push_back(token);
		}
	}
	return tokens;
}