#include <iostream>
#include <string>
#include <vector>

#include "../Logger.h"
#include "ICommand.h"
#include "ExitCommand.h"

void ExitCommand::verifyOptions()
{
	if (options.size() != 1) throw std::invalid_argument("Invalid Input Argument for Exit Command");
}

void ExitCommand::execute()
{
	exit(0);
	log();
}

void ExitCommand::log() {
	Logger* logger = Logger::getInstance();
	string className = typeid(*this).name();
	logger->write(className, options[0]);
}
