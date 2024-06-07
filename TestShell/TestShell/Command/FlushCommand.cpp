#include <iostream>
#include <string>
#include <vector>

#include "../SsdApi.h"
#include "ICommand.h"
#include "IoCommand.h"
#include "FlushCommand.h"

void FlushCommand::verifyOptions()
{
	if (options.size() != 1) throw std::invalid_argument("Invalid Input Argument for Flush Command");
}

void FlushCommand::execute()
{
	ssdApi->flush();
}
