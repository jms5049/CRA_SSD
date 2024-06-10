#pragma once

using std::string;
using std::vector;

class CommandFactory {
public:
	static CommandFactory* getCommandFactory();

	ICommand* getCommand(vector<string>& commandAndOptions);
<<<<<<< HEAD
<<<<<<< HEAD
	bool isSupportedCommand(std::string& command);
=======
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])
=======
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3

private:
	static CommandFactory* factoryInstance;
	static const vector<string> supportedCommands;

	CommandFactory() { };
<<<<<<< HEAD
<<<<<<< HEAD
=======
	bool isSupportedCommand(std::string& command);
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])
=======
	bool isSupportedCommand(std::string& command);
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
	ICommand* makeCommand(vector<string>& commandAndOptions);
};
