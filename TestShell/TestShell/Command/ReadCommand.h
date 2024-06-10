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
	void log(string readValue);
};