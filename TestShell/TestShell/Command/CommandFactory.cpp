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
<<<<<<< HEAD
<<<<<<< HEAD
#include "FlushCommand.h"
=======
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])
=======
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3

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
<<<<<<< HEAD
<<<<<<< HEAD
	"erase_range",
	"flush"
=======
	"erase_range"
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])
=======
	"erase_range"
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
};

ICommand* CommandFactory::getCommand(vector<string>& commandAndOptions)
{
	string commandName = commandAndOptions[0];
	if (isSupportedCommand(commandName) == false) return nullptr;
	return makeCommand(commandAndOptions);

}

bool CommandFactory::isSupportedCommand(std::string& command)
{
<<<<<<< HEAD
<<<<<<< HEAD
	int commandOff = command.find(' ');
	if (commandOff != -1) command = command.substr(0, commandOff);

=======
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])
=======
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
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
<<<<<<< HEAD
<<<<<<< HEAD
	if (commandName == "flush") command = new FlushCommand(commandAndOptions);
=======
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])
=======
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3

	return command;
}
