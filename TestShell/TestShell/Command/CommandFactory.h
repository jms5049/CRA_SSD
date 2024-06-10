#pragma once

using std::string;
using std::vector;

class CommandFactory {
public:
	static CommandFactory* getCommandFactory();

	ICommand* getCommand(vector<string>& commandAndOptions);
<<<<<<< HEAD
	bool isSupportedCommand(std::string& command);
=======
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])

private:
	static CommandFactory* factoryInstance;
	static const vector<string> supportedCommands;

	CommandFactory() { };
<<<<<<< HEAD
=======
	bool isSupportedCommand(std::string& command);
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])
	ICommand* makeCommand(vector<string>& commandAndOptions);
};
