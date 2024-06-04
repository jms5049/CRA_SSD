#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

int readIndex(string input) {
	if (input[0] != 'r') throw std::invalid_argument("Invalid Input Format! Must start with r");
	if (input.size() >= 8 || input[4] != ' ') throw std::invalid_argument("Invalid read input format");
	if (input.size() == 6) {
		if (!isdigit(input[5])) {
			throw std::invalid_argument("Invalid index format! Index must be 0 to 99");
		}
		return stoi(input.substr(5, 1));
	}
	if (input.size() == 7) {
		if (!isdigit(input[5]) || !isdigit(input[6])) {
			throw std::invalid_argument("Invalid index format! Index must be 0 to 99");
		}
		return stoi(input.substr(5, 2));
	}
}

string printResult(string input) {
	int idx = readIndex(input);
	string filepath = "result.txt";
	ifstream file(filepath);
	if (file.is_open()) {
		cout << "File opened successfully!" << std::endl;
		string line;
		while (getline(file, line)) {
			std::cout << line << std::endl;
		}
		file.close();
	}
	else {
		cerr << "Failed to open the file!" << endl;
	}

	return " ";
}