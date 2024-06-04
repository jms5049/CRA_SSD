#include "TestShell.h"

void TestShell::inputParser(string userInput) {
	vector<string> args = splitString(userInput);
	if (args[0] == "write") {
		if (args.size() != 3)
			throw invalid_argument("Wrong API Call use Help to See More");

		int lba = stoi(args[1]);
		int data = stoi(args[2]);

		if (lba < 0 || lba > 99)
			throw out_of_range("LBA Out of Range");

		//TO DO : call write Function args[1] : LBA , args[2] : data
		return;
	}
	if (args[0] == "read") {
		if (args.size() != 2)
			throw invalid_argument("Wrong API Call use Help to See More");

		int lba = stoi(args[1]);

		if (lba < 0 || lba > 99)
			throw out_of_range("LBA Out of Range");
		//TO DO : call read Function args[1] : LBA
		return;
	}
	if (args[0] == "exit") {
		if (args.size() != 1)
			throw invalid_argument("Wrong API Call use Help to See More");
		exitShell();
		return;
	}
	if (args[0] == "help") {
		if (args.size() != 1)
			throw invalid_argument("Wrong API Call use Help to See More");
		//TO DO : call write Function args[1] : LBA , args[2] : ADDR
		return;
	}
	if (args[0] == "fullwrite") {
		if (args.size() != 1)
			throw invalid_argument("Wrong API Call use Help to See More");
		//TO DO : call full write
		return;
	}
	if (args[0] == "fullread") {
		if (args.size() != 1)
			throw invalid_argument("Wrong API Call use Help to See More");
		//TO DO : call full read
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