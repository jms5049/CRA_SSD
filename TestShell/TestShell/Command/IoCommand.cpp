#include <iostream>
#include <string>
#include <vector>

#include "ICommand.h"
#include "IoCommand.h"

int IoCommand::verifyConvertLba(std::string& strLba, bool isEndLba) {
<<<<<<< HEAD
	verifyLbaLength(strLba, isEndLba);
=======
	verifyLbaLength(strLba, 2);
>>>>>>> 3595e5a (Master 반영 [gh pr checkout 57])
	verityLbaOnlyNumbers(strLba);
	return stoi(strLba);
}

void IoCommand::verifyLbaLength(std::string& strLba, bool isEndLba)
{
	int maxLength = 2;
	if (isEndLba == true) maxLength = 3;
	if (strLba.length() > maxLength) throw std::out_of_range("Given LBA Length is too Long");
}

void IoCommand::verityLbaOnlyNumbers(std::string& strLba)
{
	for (int i = 0; i < strLba.length(); i++) {
		if (strLba[i] < '0' || strLba[i] > '9') throw std::invalid_argument("Given LBA Length is Not in Format");
	}
}
