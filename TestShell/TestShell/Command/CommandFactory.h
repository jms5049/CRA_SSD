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
	bool isSupportedCommand(std::string& command);
	bool isSupportedCommand(std::string& command);
	ICommand* makeCommand(vector<string>& commandAndOptions);
};
