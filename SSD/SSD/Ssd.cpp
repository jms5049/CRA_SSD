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

extern vector<string> splitString(const string& str);

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
	ssdBuffer.flushBuffer();
	logger = getLLInstance();
}

string Ssd::readResult() {
	return readTxtData(resultFileName);
}

bool Ssd::checkBuffer(int lbaIndex) {
	vector<string> bufferData = ssdBuffer.readBuffer();
	for (int i = bufferData.size() - 1; i >= 0; i--) {
		string cmd = bufferData[i];
		if (cmd.find("W") == 0) {
			vector<string> args = splitString(cmd);
			int LBA = stoi(args[1]);
			string LBAData = args[2];
			if (LBA == lbaIndex) {
				updateReadResult(LBAData);
				return true;
			}
		}
		if (cmd.find("E") == 0) {
			vector<string> args = splitString(cmd);
			int startIdx = stoi(args[1]);
			int size = stoi(args[2]);
			int endIdx = startIdx + size;
			if (lbaIndex >= startIdx && lbaIndex < endIdx) {
				updateReadResult("0x00000000");
				return true;
			}
		}
	}
	return false;
}

void Ssd::readSsd(int lbaIndex) {
	string logStr = to_string(lbaIndex);
	logWrite(logger,__func__, logStr.c_str());

	if (checkBuffer(lbaIndex) == false) {
		readNandDataAndUpdateStartIndex(lbaIndex);
		if (nandData == ErrorMessage)  return;

		updateReadResult("0x" + nandData.substr(startIndex, 8));
	}
}


void Ssd::flush() {
	vector<string> bufferData = ssdBuffer.readBuffer();

	for (int i = 0; i < bufferData.size(); i++) {
		string cmd = bufferData[i];

		if (cmd.find("W") == 0) {
			vector<string> args = splitString(cmd);

			int LBA = stoi(args[1]);
			string writeData = args[2];

			writeNand(LBA, writeData);
		}
		if (cmd.find("E") == 0) {
			vector<string> args = splitString(cmd);

			int LBA = stoi(args[1]);
			int size = stoi(args[2]);

			eraseNand(LBA, size);
		}
	}

	ssdBuffer.flushBuffer();
}

void Ssd::writeSsd(int lbaIndex, string writeData) {
	string cmd = "W ";
	cmd += to_string(lbaIndex);
	cmd += " ";
	cmd += writeData;
	logWrite(logger, __func__, cmd.c_str());
	ssdBuffer.addCmnToBuffer(cmd);
	
	if (ssdBuffer.isCmd10InBuffer()) {
		flush();
	}
}

void Ssd::writeNand(int lbaIndex, string writeData) {
	readNandDataAndUpdateStartIndex(lbaIndex);
	if (nandData == ErrorMessage)  return;

	updateAndWriteNandData(writeDataSize, writeData.substr(2, 8));
}

void Ssd::eraseSsd(int lbaIndex, int size) {
	if (ssdBuffer.isEraseMerged(lbaIndex, size)) return;

	string cmd = "E ";
	cmd += to_string(lbaIndex);
	cmd += " ";
	cmd += to_string(size);
	logWrite(logger, __func__, cmd.c_str());
	ssdBuffer.addCmnToBuffer(cmd);

	if (ssdBuffer.isCmd10InBuffer()) {
		flush();
	}
}

void Ssd::eraseNand(int lbaIndex, int size) {
	readNandDataAndUpdateStartIndex(lbaIndex);
	if (nandData == ErrorMessage)  return;

	if (lbaIndex + size > lbaSize)
		size = lbaSize - lbaIndex;

	int endSize = size * writeDataSize;
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

void Ssd::readNandDataAndUpdateStartIndex(int lbaIndex) {
	nandData = readTxtData(nandFlieName);
	startIndex = lbaIndex * writeDataSize;
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
