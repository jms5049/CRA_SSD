#pragma once

class EraseCommand : public IoCommand {
public:
	EraseCommand(vector<string> options)
		: IoCommand(options) {
	}

	void verifyOptions();
	void execute();

protected:
	void divideEraseRange(int iLba, int len);
<<<<<<< HEAD
=======
private:
	void log();
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
};