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
private:
	string nandFlieName = "./nand.txt";
	string resultFileName = "./result.txt";
	string ErrorMessage = "Nand file open error!";
	const int nandCharSize = 800;
	string readTxtData(string filePath);
	void writeTxtData(string filePath, string writeData);
	string readNandData();
	void writeNandData(string changedNandData);
	void updateReadResult(string readData);
};