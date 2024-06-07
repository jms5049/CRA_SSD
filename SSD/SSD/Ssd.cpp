#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

bool Ssd::checkBuffer(int LbAIndex) {
	vector<string> bufferData = ssd_buffer.readBuffer();
	for (int i = 0; i < bufferData.size(); i++) {
		string temp = bufferData[i];
	}
	bool check = 1;
	updateReadResult("0x" + nandData.substr(startIndex, 8));
	return true;
}

void Ssd::readSsd(int LBAIndex) {
	if (checkBuffer(LBAIndex) == false) {
		readNandDataAndUpdateStartIndex(LBAIndex);
		if (nandData == ErrorMessage)  return;

		updateReadResult("0x" + nandData.substr(startIndex, 8));
	}
}

void Ssd::flush() {
	ssd_buffer.flushBuffer();
}

void Ssd::writeSsd(int LBAIndex, string writeData) {
	// Add write cmd to buffer.txt
	char index[100];
	_itoa_s(LBAIndex, index, 10);

	string cmd = "W ";
	cmd += index;
	cmd += " ";
	cmd += writeData;

	ssd_buffer.addCmnToBuffer(cmd);
	
	// Check cmd number is 10 and Do flush
	if (ssd_buffer.isCmd10InBuffer()) {
		flush();
	}
}

void Ssd::writeNand(int LBAIndex, string writeData) {
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
