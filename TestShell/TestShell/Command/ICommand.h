#pragma once

#include "../SsdApi.h"
#include "../Ssd.h"

using std::string;
using std::vector;

class ICommand {
public:
	ICommand(vector<string> options)
		: options(options) {
		ssdApi = Ssd::getInstance();
	}

	virtual void verifyOptions() = 0;
	virtual void execute() = 0;
	virtual string getResult() { return string(); }

protected:
	ssdApi* ssdApi;
	vector<string> options;
};