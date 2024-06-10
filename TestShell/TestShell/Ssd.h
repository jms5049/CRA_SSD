#pragma once
#include "SsdApi.h"

class Ssd : public SsdApi {
public:
	static Ssd* getInstance();
	void write(int lba, std::string data) override;
	void erase(int lba, int size) override;
	std::string read(int lba) override;
	void flush() override;

private:
	static const std::string SSD_LOCATION;
	static Ssd* ssd;
	Ssd();
	std::string convertToWriteCmd(int lba, std::string& data);
	std::string convertToReadCmd(int lba);
	std::string convertToEraseCmd(int lba, int size);
	std::string readResultFile(const std::string& filepath);
	void executeSsdCmd(std::string& cmdOption);
};
