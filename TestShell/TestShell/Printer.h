#pragma once
#include <string>

class Printer {
public:
	static Printer* getInstance();
	static void print(std::string& str);
	static void setIsRunner(bool isRunner);

private:
	static Printer* printer;
	static bool isRunner;
	Printer();
};
