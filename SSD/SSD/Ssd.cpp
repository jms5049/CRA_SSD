#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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

static vector<string> splitString(const string& str) {
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

bool Ssd::checkBuffer(int LBAIndex) {
	vector<string> bufferData = ssd_buffer.readBuffer();
	for (int i = bufferData.size() - 1; i >= 0; i--) {
		string cmd = bufferData[i];
		if (cmd.find("W") == 0) {
			vector<string> args = splitString(cmd);
			int LBA = stoi(args[1]);
			string LBAData = args[2];
			if (LBA == LBAIndex) {
				updateReadResult(LBAData);
				return true;
			}
		}
		if (cmd.find("E") == 0) {
			vector<string> args = splitString(cmd);
			int startIdx = stoi(args[1]);
			int size = stoi(args[2]);
			int endIdx = startIdx + size;
			if (LBAIndex >= startIdx && LBAIndex < endIdx) {
				updateReadResult("0x00000000");
				return true;
			}
		}
	}
	return false;
}

void Ssd::readSsd(int LBAIndex) {
	if (checkBuffer(LBAIndex) == false) {
		readNandDataAndUpdateStartIndex(LBAIndex);
		if (nandData == ErrorMessage)  return;

		updateReadResult("0x" + nandData.substr(startIndex, 8));
	}
}


void Ssd::flush() {
	vector<string> bufferData = ssd_buffer.readBuffer();

	for (int i = 0; i < bufferData.size(); i++) {
		string cmd = bufferData[i];

		if (cmd.find("W") == 0) {
			vector<string> args = splitString(cmd);

			int LBA = stoi(args[1]);
			string writeData = args[2];

			writeNand(LBA, writeData);
		}
		if (cmd.find("E") == 0) {
			// Todo!!!!
		}
	}

	ssd_buffer.flushBuffer();
}

void Ssd::writeSsd(int LBAIndex, string writeData) {
	string cmd = "W ";
	cmd += to_string(LBAIndex);
	cmd += " ";
	cmd += writeData;

	ssd_buffer.addCmnToBuffer(cmd);
	
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
