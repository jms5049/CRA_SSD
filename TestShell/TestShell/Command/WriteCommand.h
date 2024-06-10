#pragma once

class WriteCommand : public IoCommand {
public:
	WriteCommand(vector<string> options)
		: IoCommand(options) {
	}

	void verifyOptions() override;
	void execute() override;

protected:
	void verifyWriteDataLength(std::string& strData);
	void verifyWriteDataHexNum(std::string& writeData);
private:
	void log();
};