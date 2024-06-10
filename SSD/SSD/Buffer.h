#pragma once
#include <string>
#include <vector>
using namespace std;

class Buffer {
public:
	bool isCmd10InBuffer();
	void addCmnToBuffer(string cmd);
	void flushBuffer();
	vector<string> readBuffer();
	bool isEraseMerged(int LBAIndex, int size);

private:
	const string bufferFileName = "./buffer.txt";
}; 