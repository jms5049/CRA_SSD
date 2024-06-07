#include <string>
#include <vector>

#include "ICommand.h"
#include "CommandFactory.h"

#include "IoCommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"
#include "FullReadCommand.h"
#include "FullWriteCommand.h"
#include "HelpCommand.h"
#include "ExitCommand.h"
#include "EraseCommand.h"
#include "EraseRangeCommand.h"

using std::string;
using std::vector;

CommandFactory* CommandFactory::factoryInstance = nullptr;

CommandFactory* CommandFactory::getCommandFactory() {
	if (factoryInstance == nullptr) factoryInstance = new CommandFactory();
	return factoryInstance;
}

const vector<string> CommandFactory::supportedCommands = {
	"read",
	"write",
	"exit",
	"help",
	"fullwrite",
	"fullread",
	"erase",
	"erase_range"
};

ICommand* CommandFactory::getCommand(vector<string>& commandAndOptions)
{
	string commandName = commandAndOptions[0];
	if (isSupportedCommand(commandName) == false) return nullptr;
	return makeCommand(commandAndOptions);

}

bool CommandFactory::isSupportedCommand(std::string& command)
{
	for (auto& curCommand : supportedCommands) {
		if (command == curCommand) return true;
	}

	return false;
}

ICommand* CommandFactory::makeCommand(vector<string>& commandAndOptions)
{
	ICommand* command = nullptr;
	string commandName = commandAndOptions[0];

	if (commandName == "read") command = new ReadCommand(commandAndOptions);
	if (commandName == "write") command = new WriteCommand(commandAndOptions);
	if (commandName == "exit") command = new ExitCommand(commandAndOptions);
	if (commandName == "help") command = new HelpCommand(commandAndOptions);
	if (commandName == "fullwrite") command = new FullWriteCommand(commandAndOptions);
	if (commandName == "fullread") command = new FullReadCommand(commandAndOptions);
	if (commandName == "erase") command = new EraseCommand(commandAndOptions);
	if (commandName == "erase_range") command = new EraseRangeCommand(commandAndOptions);

	return command;
}
