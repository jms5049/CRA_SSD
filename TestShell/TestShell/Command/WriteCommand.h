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
<<<<<<< HEAD
=======
private:
	void log();
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
};