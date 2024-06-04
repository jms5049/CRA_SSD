#pragma once
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TestShell {
public:
	void inputParser(string userInput);
	void exitShell();
	void help(string command);
private:
	vector<string> splitString(const string& str);
	bool isNumber(const string& s);
	void help_write();
	void help_read();
	void help_exit();
	void help_fullwrite();
	void help_fullread();
};