#pragma once
#include <iostream>
#include <fstream>
#include <string>

using std::string;

class Ssd {
public:
	string getErrorMessage();
	void initializeResourceFile();
	string readResult();
	void readSsd(int LBAIndex);
	void writeSsd(int LBAIndex, string writeData);
	void eraseSsd(int LBAIndex, int size);
private:
	const string nandFlieName = "./nand.txt";
	const string resultFileName = "./result.txt";
	const string bufferFileName = "./buffer.txt";
	const string ErrorMessage = "Nand file open error!";
	const string EraseSource = "00000000";
	const int nandCharSize = 800;
	const int lbaSize = 100;
	const int writeDataSize = 8;
	const int maxEraseSize = 10;

	string nandData;
	int startIndex;

	string readTxtData(string filePath);
	void writeTxtData(string filePath, string writeData);
	void readNandDataAndUpdateStartIndex(int LBAIndex);
	void updateAndWriteNandData(int updateSize, string writeData);
	void updateReadResult(string readData);
	void writeNand(int LBAIndex, string writeData);
};