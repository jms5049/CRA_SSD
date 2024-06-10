#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Buffer.h"
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

void Buffer::updateBuffer(vector<string> &newBuffer) {
	ofstream file(bufferFileName, ios::trunc);
	if (file.is_open() == false)  return;

	for (auto cmd : newBuffer)
		file << cmd << endl;

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

vector<string> splitString(const string& str) {
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

bool Buffer::isWriteErasable(string cmd, EraseRange target) {
	vector<string> args = splitString(cmd);
	int LBA = stoi(args[1]);
	string LBAData = args[2];

	if (target.start <= LBA && LBA < target.end)  return true;
	
	return false;
}

bool Buffer::isEraseMergeable(string cmd, EraseRange target, vector<string> &newBuffer) {
	vector<string> args = splitString(cmd);
	int startIdx = stoi(args[1]);
	int size = stoi(args[2]);
	int endIdx = startIdx + size;

	if (startIdx <= target.start && target.start <= endIdx && endIdx < target.end) {
		size = target.end - startIdx;
	}
	else if (target.start <= startIdx && startIdx <= target.end && target.end < endIdx) {
		startIdx = target.start;
		size = endIdx - target.start;
	}
	else {
		return false;
	}
	newBuffer.push_back("E " + to_string(startIdx) + " " + to_string(size));
	return true;
}

bool Buffer::isEraseMerged(int lbaIndex, int size) {
	vector<string> buffer = readBuffer();
	vector<string> newBuffer;
	EraseRange target = { lbaIndex , lbaIndex + size };
	bool ret = false;

	for (int i = 0; i < buffer.size(); i++) {
		string cmd = buffer[i];

		if (cmd[0] == 'W' && isWriteErasable(cmd, target) == true) 	continue;
		if (cmd[0] == 'E' && isEraseMergeable(cmd, target, newBuffer) == true) {
			ret = true;
			continue;
		}
		newBuffer.push_back(cmd);
	}

	if (buffer.size() != newBuffer.size() || ret == true)  updateBuffer(newBuffer);

	return ret;
}