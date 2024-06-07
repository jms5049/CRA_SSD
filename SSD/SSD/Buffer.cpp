#include "Buffer.h"
#include <fstream>
#include <iostream>
#include <string>
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