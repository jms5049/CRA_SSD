#include <iostream>
#include <string>
#include <vector>

#include "../SsdApi.h"
#include "ICommand.h"
#include "IoCommand.h"
#include "EraseCommand.h"

void EraseCommand::verifyOptions()
{
	if (options.size() != 3) throw std::invalid_argument("Invalid Input Argument for Erase Command");
}

void EraseCommand::execute()
{
	string startLba = options[1];
	string size = options[2];
	int iLba = verifyConvertLba(startLba);
	int len = verifyConvertLba(size, true);
	if (iLba < 0 || iLba > 99) throw std::invalid_argument("Start index must be 0 to 99");
	if (len < 1 || len > 100) throw std::invalid_argument("Erasing size must be 1 to 100");
	divideEraseRange(iLba, len);
}

void EraseCommand::divideEraseRange(int iLba, int len)
{
	if (iLba + len > 100) len = 100 - iLba;
	if (len <= 10) {
		ssdApi->erase(iLba, len);
		return;
	}
	int times = len / 10;
	int residual = len % 10;
	int startIdx = iLba;

	for (int i = 0; i < times; i++) {
		ssdApi->erase(startIdx, 10);
		startIdx = startIdx + 10;
	}
	if (residual > 0) ssdApi->erase(startIdx, residual);
}