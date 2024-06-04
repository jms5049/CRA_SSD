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
private:
	string nandFlieName = "nand.txt";
	string ErrorMessage = "Nand file open error!";
};