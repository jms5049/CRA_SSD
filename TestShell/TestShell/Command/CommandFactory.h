#pragma once

using std::string;
using std::vector;

class CommandFactory {
public:
	static CommandFactory* getCommandFactory();

	ICommand* getCommand(vector<string>& commandAndOptions);
	bool isSupportedCommand(std::string& command);

private:
	static CommandFactory* factoryInstance;
	static const vector<string> supportedCommands;

	CommandFactory() { };
	ICommand* makeCommand(vector<string>& commandAndOptions);
};
