#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Ssd {
public:
	string getErrorMessage() {
		return ErrorMessage;
	}

	void initializeResourceFile() {
		ofstream nandFile(nandFlieName, ios::trunc);
		ofstream resultFile(resultFileName, ios::trunc);

		string nandInit = "";
		for (int i = 0; i < 800; i++) {
			nandInit += "0";
		}
		nandFile << nandInit;
		resultFile << "";

		nandFile.close();
		resultFile.close();
	}

	string readSsd(int LBAIndex) {
		string nandData = readNandData();

		if (nandData == ErrorMessage)  return ErrorMessage;

		int startIndex = LBAIndex * 4 * 2;
		string result = "0x" + nandData.substr(startIndex, 8);
		updateReadResult(result);
		return result;
	}

	void writeSsd(int LBAIndex, string writeData) {
		string nandData = readNandData();

		if (nandData == ErrorMessage)  return;

		int startIndex = LBAIndex * 4 * 2;
		for (int i = 0; i < 8; i++) {
			nandData[startIndex + i] = writeData[2 + i];
		}
		writeNandData(nandData);
	}
private:
	string nandFlieName = "../nand.txt";
	string resultFileName = "../result.txt";
	string ErrorMessage = "Nand file open error!";

	string readNandData() {
		ifstream file(nandFlieName);
		if (file.is_open() == false)  return ErrorMessage;

		string line;
		getline(file, line);

		file.close();
		return line;
	}

	void writeNandData(string changedNandData) {
		ofstream file(nandFlieName);
		if (file.is_open() == false)  return;
		file << changedNandData;

		file.close();
	}

	void updateReadResult(string readData) {
		ofstream file(resultFileName, ios::trunc);
		if (file.is_open() == false)  return;
		file << readData;

		file.close();
	}
};