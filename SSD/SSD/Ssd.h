#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Buffer.h"
#include "LoggerLibrary.h"

using std::string;

class Ssd {
public:
	string getErrorMessage();
	void initializeResourceFile();
	string readResult();
	void readSsd(int lbaIndex);
	void writeSsd(int lbaIndex, string writeData);
	void eraseSsd(int lbaIndex, int size);
	void flush();

private:
#if _DEBUG
	const string nandFlieName = "./nand.txt";
	const string resultFileName = "./result.txt";
#else
	const string nandFlieName = "./SSD/nand.txt";
	const string resultFileName = "./SSD/result.txt";
#endif

	const string ErrorMessage = "Nand file open error!";
	const string EraseSource = "00000000";
	const int nandCharSize = 800;
	const int lbaSize = 100;
	const int writeDataSize = 8;

	string nandData;
	int startIndex;
	Buffer ssdBuffer;

	LoggerLibrary* logger = nullptr;

	string readTxtData(string filePath);
	void writeTxtData(string filePath, string writeData);
	void readNandDataAndUpdateStartIndex(int lbaIndex);
	void updateAndWriteNandData(int updateSize, string writeData);
	void updateReadResult(string readData);
	void writeNand(int lbaIndex, string writeData);
	void eraseNand(int lbaIndex, int size);
	bool checkBuffer(int lbaIndex);
};