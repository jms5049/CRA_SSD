#pragma once

class HelpCommand : public ICommand {
public:
	HelpCommand(vector<string> options)
		: ICommand(options) {
	}

	void verifyOptions();
	void execute();

private:
	void helpWrite();
	void helpRead();
	void helpExit();
	void helpFullwrite();
	void helpFullread();
	void helpErase();
	void helpEraseRange();
	void helpFlush();
};
