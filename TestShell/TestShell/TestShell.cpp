#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#include "ShellException.h"
#include "SsdApi.h"
#include "TestShell.h"

using std::string;
using std::regex;
using std::regex_match;

TestShell::TestShell(SsdApi* ssdApi) : ssdApi(ssdApi) {
	// do nothing
}

void TestShell::inputParser(string userInput) {
	vector<string> args = splitString(userInput);

	if (args[0] == "write") {
		if (args.size() != 3) throw InvalidArgumentException();
		write(args[1], args[2]);
		return;
	}
	if (args[0] == "read") {
		if (args.size() != 2) throw InvalidArgumentException();
		read(args[1]);
		return;
	}
	if (args[0] == "exit") {
		if (args.size() != 1) throw InvalidArgumentException();
		exitShell();
	}
	if (args[0] == "help") {
		if (args.size() != 2) throw InvalidArgumentException();
		help(args[1]);
		return;
	}
	if (args[0] == "fullwrite") {
		if (args.size() != 1) throw InvalidArgumentException();
		fullWrite(args[1]);
		return;
	}
	if (args[0] == "fullread") {
		if (args.size() != 1) throw InvalidArgumentException();
		fullRead();
		return;
	}
}

void TestShell::exitShell() {
	exit(0);
}

vector<string> TestShell::splitString(const string& str) {
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

void TestShell::write(string strLba, string writeData)
{
	int iLba = verifyConvertLba(strLba);
	verifyWriteDataLength(writeData);
	verifyWriteDataHexNum(writeData);
	ssdApi->write(iLba, writeData);
}

void TestShell::fullWrite(string writeData)
{
	verifyWriteDataLength(writeData);
	verifyWriteDataHexNum(writeData);

	for (int i = 0; i < 100; i++) {
		ssdApi->write(i, writeData);
	}
}

void TestShell::verifyWriteDataHexNum(std::string& writeData)
{
	regex e("0x[0-9A-F]{8}");
	if (regex_match(writeData, e) == false) throw InvalidDataException();
}

void TestShell::verifyWriteDataLength(std::string& strData)
{
	if (strData.length() != 10) throw InvalidDataException();
}

void TestShell::read(string strLba)
{
	int iLba = verifyConvertLba(strLba);
	ssdApi->read(iLba);
	cout << readResultFile("../../SSD/result.txt") << endl;
}

void TestShell::fullRead()
{
	for (int idx = 0; idx < 100; idx++) {
		ssdApi->read(idx);
		cout << readResultFile("../../SSD/result.txt") << endl;
	}
}

int TestShell::verifyConvertLba(string& strLba) {
	int iLba = 0;
	if (strLba.length() > 2) throw InvalidLbaException();

	for (int i = 0; i < strLba.length(); i++) {
		if (strLba[i] < '0' || strLba[i] > '9') throw InvalidLbaException();
	}

	iLba = stoi(strLba);
	return iLba;
}

string TestShell::readResultFile(const std::string& filepath) {
	string content;
	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cerr << "Error: Failed to open result.txt file for reading!" << std::endl;
		return "";
	}

	std::string line;
	while (std::getline(file, line)) {
		content += line + "\n";
	}

	file.close();
	return content;
}

void TestShell::exitApp() {
	exit(0);
}

void TestShell::help(string command) {
	if (command == "write") help_write();
	else if (command == "read") help_read();
	else if (command == "exit") help_exit();
	else if (command == "fullwrite") help_fullwrite();
	else if (command == "fullread") help_fullread();
	else {
		help_write();
		help_read();
		help_exit();
		help_fullwrite();
		help_fullread();
	}
}

void TestShell::help_write() {
	printf("write:\n\t write [address] [value] => write 3 0xaabbccdd\n");
}
void TestShell::help_read() {
	printf("read:\n\t read [address] => read 3 \n");
}
void TestShell::help_exit() {
	printf("exit:\n\t you can exit the program \n");
}
void TestShell::help_fullwrite() {
	printf("fullwrite:\n\t you can write overall region at once \n\t fullwrite [value] => fullwrite 0xabcdffff \n");
}
void TestShell::help_fullread() {
	printf("fullread:\n\t you can read overall region at once\n");
}
