#pragma once

class FullReadCommand : public ReadCommand {
public:
	FullReadCommand(vector<string> options)
		: ReadCommand(options) {
	}

	void verifyOptions();
	void execute();
<<<<<<< HEAD
=======
private:
	void log();
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
};