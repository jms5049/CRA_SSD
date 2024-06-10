#pragma once
#include <string>
#include <vector>
using namespace std;

struct EraseRange {
	int start;
	int end;
};

class Buffer {
public:
	bool isCmd10InBuffer();
	void addCmnToBuffer(string cmd);
	void flushBuffer();
	vector<string> readBuffer();
	bool isEraseMerged(int lbaIndex, int size);

private:
#if _DEBUG
	const string bufferFileName = "./buffer.txt";
#else
	const string bufferFileName = "./SSD/buffer.txt";
#endif
	void updateBuffer(vector<string>& newBuffer);
	bool isWriteErasable(string cmd, EraseRange target);
	bool isEraseMergeable(string cmd, EraseRange target, vector<string> &newBuffer);
}; 