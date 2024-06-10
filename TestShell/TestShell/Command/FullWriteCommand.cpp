#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "../SsdApi.h"
<<<<<<< HEAD
=======
#include "../Logger.h"
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
#include "ICommand.h"
#include "IoCommand.h"
#include "WriteCommand.h"
#include "FullWriteCommand.h"

void FullWriteCommand::verifyOptions()
{
	if (options.size() != 2) throw std::invalid_argument("Invalid Input Argument for Full Write Command");
}

void FullWriteCommand::execute()
{
	string writeData = options[1];
	verifyWriteDataLength(writeData);
	verifyWriteDataHexNum(writeData);

	for (int i = 0; i < 100; i++) {
		ssdApi->write(i, writeData);
	}
<<<<<<< HEAD
}
=======
	log();
}

void FullWriteCommand::log()
{
	Logger* logger = Logger::getInstance();
	string className = typeid(*this).name();
	logger->write(className, options[1]);
}
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
