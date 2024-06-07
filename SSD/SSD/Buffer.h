#pragma once
#include <string>
using namespace std;

class Buffer {
public:
	bool isCmd10InBuffer();
	void addCmnToBuffer(string cmd);

private:
	const string bufferFileName = "./buffer.txt";
}; 