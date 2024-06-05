#pragma once
#include "SsdApi.h"

class Ssd : public SsdApi {
public:
	void write(int lba, std::string data) override;
	std::string read(int lba) override;

private:
	static const std::string SSD_LOCATION;

	std::string convertToWriteCmd(int lba, std::string& data);
	std::string convertToReadCmd(int lba);
	std::string readResultFile(const std::string& filepath);
};
