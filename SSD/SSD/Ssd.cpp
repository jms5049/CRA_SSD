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
	readNandDataAndUpdateStartIndex(LBAIndex);
	if (nandData == ErrorMessage)  return;

	updateReadResult("0x" + nandData.substr(startIndex, 8));
}

void Ssd::writeSsd(int LBAIndex, string writeData) {
	readNandDataAndUpdateStartIndex(LBAIndex);
	if (nandData == ErrorMessage)  return;

	updateAndWriteNandData(writeDataSize, writeData.substr(2, 8));
}

void Ssd::eraseSsd(int LBAIndex, int size) {
	readNandDataAndUpdateStartIndex(LBAIndex);
	if (nandData == ErrorMessage)  return;

	if (LBAIndex + size > lbaSize)
		size = lbaSize - LBAIndex;

	int endSize = size >= maxEraseSize ? (maxEraseSize * writeDataSize) : (size * writeDataSize);
	updateAndWriteNandData(endSize, EraseSource);
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

void Ssd::readNandDataAndUpdateStartIndex(int LBAIndex) {
	nandData = readTxtData(nandFlieName);
	startIndex = LBAIndex * writeDataSize;
}

void Ssd::updateAndWriteNandData(int updateSize, string writeData) {
	for (int i = 0; i < updateSize; i++) {
		nandData[startIndex + i] = writeData[i % writeDataSize];
	}
	writeTxtData(nandFlieName, nandData);
}

void Ssd::updateReadResult(string readData) {
	writeTxtData(resultFileName, readData);
}
