#pragma once

class FullReadCommand : public ReadCommand {
public:
	FullReadCommand(vector<string> options)
		: ReadCommand(options) {
	}

	void verifyOptions();
	void execute();
};