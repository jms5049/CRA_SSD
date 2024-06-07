#include <iostream>
#include <string>
#include <vector>

#include "../SsdApi.h"
#include "ICommand.h"
#include "IoCommand.h"
#include "EraseCommand.h"
#include "EraseRangeCommand.h"

void EraseRangeCommand::verifyOptions()
{
	if (options.size() != 3) throw std::invalid_argument("Invalid Input Argument for Erase Range Command");
}

void EraseRangeCommand::execute()
{
	string startLba = options[1];
	string endLba = options[2];
	int startIdx = verifyConvertLba(startLba);
	int endIdx = verifyConvertLba(endLba, true);
	if (startIdx < 0 || startIdx > 99) throw std::invalid_argument("Start index must be 0 to 99");
	if (endIdx < 1 || endIdx > 100) throw std::invalid_argument("End index must be 1 to 100");

	int len = endIdx - startIdx;
	if (len < 1) throw std::invalid_argument("Erasing size must be 1 to 100");
	divideEraseRange(startIdx, len);
}