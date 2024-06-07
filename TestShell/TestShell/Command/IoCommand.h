#pragma once

class IoCommand : public ICommand {
public:
protected:
	IoCommand(vector<string> options)
		: ICommand(options) {
	}

	int verifyConvertLba(std::string& strLba, bool isEndLba = false);
	void verifyLbaLength(std::string& strLba, bool isEndLba);
	void verityLbaOnlyNumbers(std::string& strLba);
};