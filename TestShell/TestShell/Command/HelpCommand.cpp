#include <iostream>
#include <string>
#include <vector>

#include "ICommand.h"
#include "HelpCommand.h"

void HelpCommand::verifyOptions()
{
	if (options.size() > 2) throw std::invalid_argument("Invalid Input Argument for Help Command");
}

void HelpCommand::execute()
{
	string command = "";

	if (options.size() == 2)
		command = options[1];

	if (command == "write") helpWrite();
	else if (command == "read") helpRead();
	else if (command == "exit") helpExit();
	else if (command == "fullwrite") helpFullwrite();
	else if (command == "fullread") helpFullread();
	else if (command == "erase") helpErase();
	else if (command == "erase_range") helpEraseRange();
	else if (command == "flush") helpFlush();
	else {
		helpWrite();
		helpRead();
		helpExit();
		helpFullwrite();
		helpFullread();
		helpErase();
		helpEraseRange();
		helpFlush();
	}
}

void HelpCommand::helpWrite() {
	printf("write:\n\t write [address] [value] => write 3 0xaabbccdd\n");
}

void HelpCommand::helpRead() {
	printf("read:\n\t read [address] => read 3 \n");
}

void HelpCommand::helpExit() {
	printf("exit:\n\t you can exit the program \n");
}

void HelpCommand::helpFullwrite() {
	printf("fullwrite:\n\t you can write overall region at once \n\t fullwrite [value] => fullwrite 0xabcdffff \n");
}

void HelpCommand::helpFullread() {
	printf("fullread:\n\t you can read overall region at once\n");
}

void HelpCommand::helpErase() {
	printf("erase:\n\t erase [address] [size] => erase 3 5 \n");
}

void HelpCommand::helpEraseRange() {
	printf("erase_range:\n\t erase_range [start address] [end address] => erase_range 0 5 \n");
}

void HelpCommand::helpFlush() {
	printf("flush:\n\t flush all commands in buffer \n");
}