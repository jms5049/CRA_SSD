#pragma once

class FlushCommand : public IoCommand {
public:
	FlushCommand(vector<string> options)
		: IoCommand(options) {
	}

	void verifyOptions() override;
	void execute() override;
};