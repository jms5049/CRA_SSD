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
	void helpFullWrite();
	void helpFullRead();
	void helpErase();
	void helpEraseRange();
	void helpFlush();
};
