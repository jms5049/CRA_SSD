#include <iostream>
#include <fstream>
#include <string>

#include "Ssd.h"

using std::string;
using std::ofstream;
using std::ifstream;
using std::ios;

string Ssd::getErrorMessage() {
	return ErrorMessage;
}

void Ssd::initializeResourceFile() {
	ofstream nandFile(nandFlieName, ios::trunc);
	ofstream resultFile(resultFileName, ios::trunc);

	string nandInit = "";
	for (int i = 0; i < nandCharSize; i++) {
		nandInit += "0";
	}
	nandFile << nandInit;
	resultFile << "";

	nandFile.close();
	resultFile.close();
}

string Ssd::readResult() {
	return readTxtData(resultFileName);
}

void Ssd::readSsd(int LBAIndex) {
	string nandData = readNandData();

	if (nandData == ErrorMessage)  return;

	int startIndex = LBAIndex * 4 * 2;
	updateReadResult("0x" + nandData.substr(startIndex, 8));
}

void Ssd::writeSsd(int LBAIndex, string writeData) {
	string nandData = readNandData();

	if (nandData == ErrorMessage)  return;

	int startIndex = LBAIndex * 4 * 2;
	for (int i = 0; i < 8; i++) {
		nandData[startIndex + i] = writeData[2 + i];
	}
	writeNandData(nandData);
}

	

string Ssd::readTxtData(string filePath) {
	ifstream file(filePath);
	if (file.is_open() == false)  return ErrorMessage;

	string line;
	getline(file, line);

	file.close();
	return line;
}

void Ssd::writeTxtData(string filePath, string writeData) {
	ofstream file(filePath, ios::trunc);
	if (file.is_open() == false)  return;
	file << writeData;

	file.close();
}

string Ssd::readNandData() {
	return readTxtData(nandFlieName);
}

void Ssd::writeNandData(string changedNandData) {
	writeTxtData(nandFlieName, changedNandData);
}

void Ssd::updateReadResult(string readData) {
	writeTxtData(resultFileName, readData);
}
