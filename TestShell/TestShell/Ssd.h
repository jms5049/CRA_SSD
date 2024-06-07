#pragma once
#include "SsdApi.h"
#include "Logger.h"

class Ssd : public SsdApi {
public:
	static Ssd* getInstance(Logger* logger);
	void write(int lba, std::string data) override;
	void erase(int lba, int size) override;
	std::string read(int lba) override;

private:
	static const std::string SSD_LOCATION;
	static Ssd* ssd;
	Logger* logger;
	Ssd(Logger* logger);
	std::string convertToWriteCmd(int lba, std::string& data);
	std::string convertToReadCmd(int lba);
	std::string convertToEraseCmd(int lba, int size);
	std::string readResultFile(const std::string& filepath);
	void executeSsdCmd(std::string& cmdOption);
};
