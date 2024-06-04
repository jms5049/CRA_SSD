#include <string>
#include <regex>

#include "ShellException.h"
#include "SsdApi.h"
#include "TestShell.h"

using std::string;
using std::regex;
using std::regex_match;

TestShell::TestShell(SsdApi* ssdApi)
: ssdApi(ssdApi) {
	// do nothing
}

void TestShell::write(string input)
{
	int spacePos = input.find(' ');
	string strLba = input.substr(0, spacePos);
	string strData = input.substr(spacePos+1, input.length());

	if (spacePos == string::npos || spacePos == 0) throw InvalidCommandException();
	if (strLba.length() > 2) throw InvalidCommandException();
	if (strData.length() > 10) throw InvalidCommandException();

	for (int i = 0; i < strLba.length(); i++) {
		if (strLba[i] < '0' || strLba[i] > '9') throw InvalidCommandException();
	}

	if (strData[0] != '0' || strData[1] != 'x') throw InvalidCommandException();
	for (int i = 2; i < strData.length(); i++) {
		if (((strData[i] >= '0' && strData[i] <= '9')
			|| (strData[i] >= 'a' && strData[i] <= 'f')
			|| (strData[i] >= 'A' && strData[i] <= 'F')) == false)
		{
			throw InvalidCommandException();
		}
	}

	int iLba = atoi(strLba.data());
	string temp = strData.data();
	int iData = strtoul(strData.substr(2).data(), nullptr, 16);

	ssdApi->write(iLba, iData);
}
