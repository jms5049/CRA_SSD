#include <iostream>
#include <string>

#include "Printer.h"

using std::string;

Printer* Printer::printer = nullptr;
bool Printer::isRunner = false;

Printer::Printer() {
	// do nothing
}

Printer* Printer::getInstance() {
	if (printer == nullptr) {
		printer = new Printer();
	}
	return printer;
}

void Printer::print(string& str) {
	if (isRunner != true) std::cout << str;
}

void Printer::setIsRunner(bool isRunner) {
	printer->isRunner = isRunner;
}
