#include <iostream>
#include <string>
#include <vector>

#include "../SsdApi.h"
#include "../Logger.h"
#include "ICommand.h"
#include "IoCommand.h"
#include "ReadCommand.h"

using std::cout;
using std::endl;

void ReadCommand::verifyOptions()
{
	if (options.size() != 2) throw std::invalid_argument("Invalid Input Argument for Read Command");
}

void ReadCommand::execute()
{
	int iLba = verifyConvertLba(options[1]);
	string result = ssdApi->read(iLba);
	cout << result << endl;
	readResult = result;
	log(result);
}

void ReadCommand::log(string readValue)
{
	Logger* logger = Logger::getInstance();
	string className = typeid(*this).name();
	string strLog = "ADDR";
	strLog += options[1].c_str();
	strLog += "=>";
	strLog += readValue;
	logger->write(className, strLog);
}
