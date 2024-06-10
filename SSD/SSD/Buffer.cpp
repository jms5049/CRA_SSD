#include "Buffer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

bool Buffer::isCmd10InBuffer() {
	ifstream file(bufferFileName);
	if (file.is_open() == false)  return false;

	int cnt = 0;
	string line;
	while (getline(file, line))
		cnt++;

	if (cnt < 10) return false;
	return true;
}

void Buffer::addCmnToBuffer(string cmd) {
	ofstream file(bufferFileName, ios::app);
	if (file.is_open() == false)  return;
	file << cmd << endl;

	file.close();
}

void Buffer::flushBuffer() {
	ofstream file(bufferFileName, ios::trunc);
	file.close();
}

vector<string> Buffer::readBuffer() {
	vector<string> bufferData;
	ifstream file(bufferFileName);

	if (!file.is_open()) cerr << "Error opening file!" << endl;

	string line;
	while (getline(file, line)) {
		bufferData.push_back(line);
	}

	file.close();
	return bufferData;
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

bool Buffer::isEraseMerged(int LBAIndex, int size) {
	vector<string> buffer = readBuffer();
	vector<string> newBuffer;
	int targetStart = LBAIndex;
	int targetEnd = LBAIndex + size;
	bool ret = false;

	for (int i = 0; i < buffer.size(); i++) {
		string cmd = buffer[i];

		if (cmd[0] == 'W') {
			vector<string> args = splitString(cmd);
			int LBA = stoi(args[1]);
			string LBAData = args[2];
			if (targetStart <= LBA && LBA < targetEnd) {
				continue;
			}

		}
		else if (cmd[0] == 'E') {
			vector<string> args = splitString(cmd);
			int startIdx = stoi(args[1]);
			int size = stoi(args[2]);
			int endIdx = startIdx + size;

			if (startIdx <= targetStart && targetStart <= endIdx && endIdx < targetEnd) {
				size = targetEnd - startIdx;
				newBuffer.push_back("E " + to_string(startIdx) + " " + to_string(size));
				ret = true;
				continue;
			}
			else if (targetStart <= startIdx && startIdx <= targetEnd && targetEnd < endIdx) {
				startIdx = targetStart;
				size = endIdx - targetStart;
				newBuffer.push_back("E " + to_string(startIdx) + " " + to_string(size));
				ret = true;
				continue;
			}
		}
		newBuffer.push_back(cmd);
	}

	if (buffer.size() != newBuffer.size() || ret == true) {
		flushBuffer();
		for(auto &cmd : newBuffer)  addCmnToBuffer(cmd);
	}

	return ret;
}