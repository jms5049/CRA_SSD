#pragma once

class ExitCommand : public ICommand {
public:
	ExitCommand(vector<string> options)
		: ICommand(options) {
	}

	void verifyOptions();
	void execute();
private:
	void log();
};