#pragma once

class HelpCommand : public ICommand {
public:
	HelpCommand(vector<string> options)
		: ICommand(options) {
	}

	void verifyOptions();
	void execute();

private:
	void help_write();
	void help_read();
	void help_exit();
	void help_fullwrite();
	void help_fullread();
};
