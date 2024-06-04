#pragma once
#include <string>

using std::string;

class TestShell {
public:
	TestShell(SsdApi* ssdApi);
	void write(string input);

private:
	SsdApi* ssdApi;
};