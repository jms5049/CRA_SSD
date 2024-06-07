#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <exception>

#include "SsdApi.h"
#include "TestShell.h"

using std::string;
using std::regex;
using std::regex_match;

TestShell::TestShell(SsdApi* ssdApi) : ssdApi(ssdApi) {
	// do nothing
}

TestShell* TestShell::testShell = nullptr;

TestShell* TestShell::getInstance(SsdApi* ssdApi)
{
	if (testShell == nullptr) {
		testShell = new TestShell(ssdApi);
	}

	return testShell;
}

void TestShell::inputParser(string userInput) {
	vector<string> args = splitString(userInput);

	if (args[0] == "write") {
		if (args.size() != 3) throw std::invalid_argument("Invalid Input Argument for Write Command");
		write(args[1], args[2]);
		return;
	}
	if (args[0] == "read") {
		if (args.size() != 2) throw std::invalid_argument("Invalid Input Argument for Read Command");
		read(args[1]);
		return;
	}
	if (args[0] == "exit") {
		if (args.size() != 1) throw std::invalid_argument("Invalid Input Argument for Exit Command");
		exitShell();
	}
	if (args[0] == "help") {
		if (args.size() > 2) throw std::invalid_argument("Invalid Input Argument for Help Command");
		help(args[1]);
		return;
	}
	if (args[0] == "fullwrite") {
		if (args.size() != 2) throw std::invalid_argument("Invalid Input Argument for Full Write Command");
		fullWrite(args[1]);
		return;
	}
	if (args[0] == "fullread") {
		if (args.size() != 1) throw std::invalid_argument("Invalid Input Argument for Full Read Command");
		fullRead();
		return;
	}
	if (args[0] == "erase") {
		if (args.size() != 3) throw std::invalid_argument("Invalid Input Argument for Erase Command");
		erase(args[1], args[2]);
		return;
	}
	if (args[0] == "erase_range") {
		if (args.size() != 3) throw std::invalid_argument("Invalid Input Argument for Erase Range Command");
		erase_range(args[1], args[2]);
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
	if (regex_match(writeData, e) == false) throw std::invalid_argument("Given Data Length is Not in Format");
}

void TestShell::verifyWriteDataLength(std::string& strData)
{
	if (strData.length() > 10) throw std::out_of_range("Given Data Length is too Long");
}

string TestShell::read(string strLba)
{
	int iLba = verifyConvertLba(strLba);
	string result = ssdApi->read(iLba);
	cout << result << endl;
	return result;
}

void TestShell::fullRead()
{
	for (int idx = 0; idx < 100; idx++) {
		cout << idx << " " << ssdApi->read(idx) << endl;
	}
}

void TestShell::erase(string startLba, string size)
{
	int iLba = verifyConvertLba(startLba);
	int len = verifyConvertLba_3(size);
	if(iLba < 0 || iLba > 99) throw std::invalid_argument("Start index must be 0 to 99");
	if(len < 1 || len > 100) throw std::invalid_argument("Erasing size must be 1 to 100");
	divideEraseRange(iLba, len);
}

void TestShell::divideEraseRange(int iLba, int len)
{
	if (iLba + len > 100) len = 100 - iLba;
	if (len <= 10) {
		ssdApi->erase(iLba, len);
		return;
	}
	int times = len / 10;
	int residual = len % 10;
	int startIdx = iLba;

	for (int i = 0; i < times; i++) {
		ssdApi->erase(startIdx, 10);
		startIdx = startIdx + 10;
	}
	if (residual > 0) ssdApi->erase(startIdx , residual);

}

void TestShell::erase_range(string startLba, string endLba)
{
	int startIdx = verifyConvertLba(startLba);
	int endIdx = verifyConvertLba_3(endLba);
	if (startIdx < 0 || startIdx > 99) throw std::invalid_argument("Start index must be 0 to 99");
	if (endIdx < 1 || endIdx > 100) throw std::invalid_argument("End index must be 1 to 100");
	
	int len = endIdx - startIdx;
	if(len < 1) throw std::invalid_argument("Erasing size must be 1 to 100");
	divideEraseRange(startIdx, len);
}


int TestShell::verifyConvertLba(string& strLba) {
	int iLba = 0;
	if (strLba.length() > 2) throw std::out_of_range("Given LBA Length is too Long");

	for (int i = 0; i < strLba.length(); i++) {
		if (strLba[i] < '0' || strLba[i] > '9') throw std::invalid_argument("Given LBA Length is Not in Format");
	}

	iLba = stoi(strLba);
	return iLba;
}

int TestShell::verifyConvertLba_3(string& strLba) {
	int iLba = 0;
	if (strLba.length() > 3) throw std::out_of_range("Given LBA Length is too Long");

	for (int i = 0; i < strLba.length(); i++) {
		if (strLba[i] < '0' || strLba[i] > '9') throw std::invalid_argument("Given LBA Length is Not in Format");
	}

	iLba = stoi(strLba);
	return iLba;
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
	else if (command == "erase") help_erase();
	else if (command == "erase_range") help_erase_range();
	else {
		help_write();
		help_read();
		help_exit();
		help_fullwrite();
		help_fullread();
		help_erase();
		help_erase_range();
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
void TestShell::help_erase() {
	printf("erase:\n\t erase [address] [size] => erase 3 5 \n");
}
void TestShell::help_erase_range() {
	printf("erase_range:\n\t erase_range [start address] [end address] => erase 0 5 \n");
}