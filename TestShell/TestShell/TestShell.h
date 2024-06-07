#pragma once
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TestShell {
public:
	static TestShell* getInstance(SsdApi* ssdApi);

	void write(string strLba, string strData);
	string read(string strLba);
	void fullRead();
	void exitApp();
	void inputParser(string userInput);
	void exitShell();
	void help(string command);
	void fullWrite(string input);

private:
	static TestShell* testShell;
	SsdApi* ssdApi;

	TestShell(SsdApi* ssdApi);
	vector<string> splitString(const string& str);
	void verifyWriteDataLength(std::string& strData);
	void verifyWriteDataHexNum(std::string& writeData);
	int verifyConvertLba(std::string& strLba);

	string readResultFile(const std::string& filepath);
	void help_write();
	void help_read();
	void help_exit();
	void help_fullwrite();
	void help_fullread();
};