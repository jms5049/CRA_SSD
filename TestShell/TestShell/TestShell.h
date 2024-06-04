#pragma once
#include <string>

using std::string;

class TestShell {
public:
	void exitApp();
	void help(string command);
private:
	void help_write();
	void help_read();
	void help_exit();
	void help_fullwrite();
	void help_fullread();
};