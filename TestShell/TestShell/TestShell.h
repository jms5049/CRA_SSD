#pragma once
#include <string>

using std::string;

class TestShell {
public:
	void exitApp();
	int help(string command);
};