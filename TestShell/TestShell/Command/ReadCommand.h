#pragma once

class ReadCommand : public IoCommand {
public:
	ReadCommand(vector<string> options)
		: IoCommand(options) {
	}

	void verifyOptions() override;
	void execute() override;
	virtual string getResult() { return readResult; };

private:
	string readResult;
<<<<<<< HEAD
=======
	void log();
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
};