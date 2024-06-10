#pragma once

class EraseRangeCommand : public EraseCommand {
public:
	EraseRangeCommand(vector<string> options)
		: EraseCommand(options) {
	}

	void verifyOptions();
	void execute();
private:
	void log();
};