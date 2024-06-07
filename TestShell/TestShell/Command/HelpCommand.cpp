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
	string command = options[1];

	if (command == "write") help_write();
	else if (command == "read") help_read();
	else if (command == "exit") help_exit();
	else if (command == "fullwrite") help_fullwrite();
	else if (command == "fullread") help_fullread();
	else {
		help_write();
		help_read();
		help_exit();
		help_fullwrite();
		help_fullread();
	}
}

void HelpCommand::help_write() {
	printf("write:\n\t write [address] [value] => write 3 0xaabbccdd\n");
}

void HelpCommand::help_read() {
	printf("read:\n\t read [address] => read 3 \n");
}

void HelpCommand::help_exit() {
	printf("exit:\n\t you can exit the program \n");
}

void HelpCommand::help_fullwrite() {
	printf("fullwrite:\n\t you can write overall region at once \n\t fullwrite [value] => fullwrite 0xabcdffff \n");
}

void HelpCommand::help_fullread() {
	printf("fullread:\n\t you can read overall region at once\n");
}
