#include <iostream>
#include <string>
#include <vector>

#include "../SsdApi.h"
#include "../Logger.h"
#include "ICommand.h"
#include "IoCommand.h"
#include "ReadCommand.h"
#include "FullReadCommand.h"

using std::cout;
using std::endl;

void FullReadCommand::verifyOptions()
{
	if (options.size() != 1) throw std::invalid_argument("Invalid Input Argument for Full Read Command");
}

void FullReadCommand::execute()
{
	for (int idx = 0; idx < 100; idx++) {
		cout << idx << " " << ssdApi->read(idx) << endl;
	}
	log();
}

void FullReadCommand::log()
{
	Logger* logger = Logger::getInstance();
	string className = typeid(*this).name();
	logger->write(className, " ");
}

