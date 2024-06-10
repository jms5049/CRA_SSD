#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "../SsdApi.h"
#include "../Logger.h"
#include "ICommand.h"
#include "IoCommand.h"
#include "WriteCommand.h"

using std::regex;
using std::regex_match;

void WriteCommand::verifyOptions()
{
	if (options.size() != 3) throw std::invalid_argument("Invalid Input Argument for Write Command");
}

void WriteCommand::execute()
{
	string writeData = options[2];
	int iLba = verifyConvertLba(options[1]);
	verifyWriteDataLength(writeData);
	verifyWriteDataHexNum(writeData);

	ssdApi->write(iLba, writeData);
	log();
}

void WriteCommand::verifyWriteDataHexNum(std::string& writeData)
{
	regex e("0x[0-9A-F]{8}");
	if (regex_match(writeData, e) == false) throw std::invalid_argument("Given Data Length is Not in Format");
}

void WriteCommand::verifyWriteDataLength(std::string& strData)
{
	if (strData.length() > 10) throw std::out_of_range("Given Data Length is too Long");
}

void WriteCommand::log()
{
	Logger* logger = Logger::getInstance();
	string className = typeid(*this).name();
	string strLog = "ADDR:";
	strLog += options[1];
	strLog += " " + options[2];
	logger->write(className, strLog);
}
