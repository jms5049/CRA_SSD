#pragma once

class EraseRangeCommand : public EraseCommand {
public:
	EraseRangeCommand(vector<string> options)
		: EraseCommand(options) {
	}

	void verifyOptions();
	void execute();
<<<<<<< HEAD
=======
private:
	void log();
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
};