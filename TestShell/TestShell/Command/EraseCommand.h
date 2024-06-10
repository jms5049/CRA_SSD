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
private:
	void log();
};