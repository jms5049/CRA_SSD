#pragma once
#include "SsdApi.h"

class Ssd : public SsdApi {
public:
	void write(int lba, std::string data) override;
	int read(int lba) override;

private:
	static const LPCSTR SSD_LOCATION;

	std::string convertToWriteCmd(int lba, std::string& data);
};
