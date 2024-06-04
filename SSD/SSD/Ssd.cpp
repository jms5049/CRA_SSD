#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Ssd {
public:
	string getErrorMessage() {
		return ErrorMessage;
	}

	string readNandData(string fileName) {
		ifstream file(fileName);

		if (file.is_open() == false)  return ErrorMessage;
		
		string line;
		getline(file, line);

		file.close();
		return line;
	}

	void writeNandData(string fileName, string changedNandData) {
		ofstream file(fileName);

		if (file.is_open() == false)  return;
		file << changedNandData;

		file.close();
	}

	string readSsd(int LBAIndex) {
		string nandData = readNandData(nandFlieName);

		if (nandData == ErrorMessage)  return ErrorMessage;

		int startIndex = LBAIndex * 4 * 2;
		return "0x" + nandData.substr(startIndex, 8);
	}

	void writeSsd(int LBAIndex, string writeData) {
		string nandData = readNandData(nandFlieName);

		if (nandData == ErrorMessage)  return;

		int startIndex = LBAIndex * 4 * 2;
		for (int i = 0; i < 8; i++) {
			nandData[startIndex + i] = writeData[i];
		}
		writeNandData(nandFlieName, nandData);
	}
private:
	string nandFlieName = "../nand.txt";
	string ErrorMessage = "Nand file open error!";
};