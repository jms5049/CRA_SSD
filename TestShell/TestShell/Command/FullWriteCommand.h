#pragma once

class FullWriteCommand : public WriteCommand {
public:
	FullWriteCommand(vector<string> options)
		: WriteCommand(options) {
	}

	void verifyOptions() override;
	void execute() override;
};