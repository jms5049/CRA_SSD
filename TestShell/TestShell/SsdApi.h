#pragma once
#include <string>

#define interface struct

interface SsdApi {
	virtual void write(int lba, std::string data) = 0;
	virtual int read(int lba) = 0;
};
