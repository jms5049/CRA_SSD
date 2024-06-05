#pragma once
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TestShell {
public:
	TestShell(SsdApi* ssdApi);
	void write(string input);
<<<<<<< feature/read_refactoring
	void read(string input);
	void exitApp();
=======
	void inputParser(string userInput);
	void exitShell();
>>>>>>> master
	void help(string command);

private:
	vector<string> splitString(const string& str);
	SsdApi* ssdApi;
	void verifyWriteInput(int spacePos, std::string& strLba, std::string& strData);
<<<<<<< feature/read_refactoring
	int verifyReadInput(string input);
=======
>>>>>>> master
	void help_write();
	void help_read();
	void help_exit();
	void help_fullwrite();
	void help_fullread();
};