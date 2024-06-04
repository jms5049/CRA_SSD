#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Ssd {
public:
	string getErrorMessage() {
		return ErrorMessage;
	}

	string readNandData(string fileName) {
		ifstream file(fileName);

		if (file.is_open() == false)  return ErrorMessage;
		
		string line;
		getline(file, line);

		file.close();
		return line;
	}

	string readSsd(int LBAIndex) {
		string nandData = readNandData(nandFlieName);

		if (nandData == ErrorMessage)  return ErrorMessage;

		int startIndex = LBAIndex * 4 * 2;
		return "0x" + changeEndian(nandData.substr(startIndex, 8));
	}

private:
	string nandFlieName = "../nand.txt";
	string ErrorMessage = "Nand file open error!";
	string changeEndian(string hexWord) {
		string ret = hexWord.substr(6, 2)
			+ hexWord.substr(4, 2)
			+ hexWord.substr(2, 2)
			+ hexWord.substr(0, 2);
		return ret;
	}
};