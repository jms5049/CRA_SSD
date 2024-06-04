#pragma once
#include <string>

using std::string;

class TestShell {
public:
	TestShell(SsdApi* ssdApi);
	void write(string input);
	void exitApp();
	void help(string command);

private:
	SsdApi* ssdApi;

	void verifyWriteInput(int spacePos, std::string& strLba, std::string& strData);

	void help_write();
	void help_read();
	void help_exit();
	void help_fullwrite();
	void help_fullread();
};