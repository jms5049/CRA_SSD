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

	string readResult() {
		return readTxtData(resultFileName);
	}

	void readSsd(int LBAIndex) {
		string nandData = readNandData();

		if (nandData == ErrorMessage)  return;

		int startIndex = LBAIndex * 4 * 2;
		updateReadResult("0x" + nandData.substr(startIndex, 8));
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
	string nandFlieName = "./nand.txt";
	string resultFileName = "./result.txt";
	string ErrorMessage = "Nand file open error!";

	string readTxtData(string filePath) {
		ifstream file(filePath);
		if (file.is_open() == false)  return ErrorMessage;

		string line;
		getline(file, line);

		file.close();
		return line;
	}

	void writeTxtData(string filePath, string writeData) {
		ofstream file(filePath, ios::trunc);
		if (file.is_open() == false)  return;
		file << writeData;

		file.close();
	}

	string readNandData() {
		return readTxtData(nandFlieName);
	}

	void writeNandData(string changedNandData) {
		writeTxtData(nandFlieName, changedNandData);
	}

	void updateReadResult(string readData) {
		writeTxtData(resultFileName, readData);
	}
};