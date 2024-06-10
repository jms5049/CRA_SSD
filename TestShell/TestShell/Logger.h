#pragma once

class Logger {
public:
    static Logger* getInstance();
    void write(std::string funcName, std::string strLog);

private:
    Logger();
    static Logger* logger;

    static void fileWrite(std::tm* curTime, std::string funcName, std::string strLog);
    static void zipFile(std::string* newFileName);
    static bool isOverflow();
    static void saveLogFileWithTime();
    static std::string getNowFileName();
    static void checkOverflowAndSaveFile();
    static void changeFileToZip();
    static void copyFile(std::string sourceFileName, std::string targetFileName);
};