#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Ssd {
public:
	string readNandData(string fileName) {
		ifstream file(fileName);

		if (file.is_open() == false) {
			return "Nand file open error!";
		}
		string line;
		getline(file, line);

		file.close();
		return line;
	}
};