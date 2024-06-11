#pragma once
#include "LoggerLibrary.h"
class Logger {
public:
    static Logger* getInstance();
    void write(std::string funcName, std::string strLog);

private:
    Logger();
    static Logger* logger;
    LoggerLibrary* loggerLB = nullptr;

    void fileWrite(std::tm* curTime, std::string funcName, std::string strLog);
    bool isOverflow();
    void saveLogFileWithTime();
    std::string getNowFileName();
    void checkOverflowAndSaveFile();
    void changeFileToZip();
    void copyFile(std::string sourceFileName, std::string targetFileName);
};