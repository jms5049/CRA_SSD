#include "Buffer.h"
#include <fstream>
#include <iostream>
using namespace std;

bool Buffer::isCmd10InBuffer() {
	return true;
}

void Buffer::addCmnToBuffer(string cmd) {
	ofstream file(bufferFileName, ios::ate);
	if (file.is_open() == false)  return;
	file << cmd;

	file.close();
}