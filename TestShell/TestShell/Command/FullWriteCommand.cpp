#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "../SsdApi.h"
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
}
