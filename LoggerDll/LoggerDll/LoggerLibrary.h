// LoggerLibrary.h - Contains declarations of math functions
#pragma once

#include <string>

#ifdef LOGGERLIBRARY_EXPORTS
#define LOGGERLIBRARY_API __declspec(dllexport)
#else
#define LOGGERLIBRARY_API __declspec(dllimport)
#endif


class LoggerLibrary {
public:
    static LoggerLibrary* getInstance();
    //void write(std::string funcName, std::string strLog);
    void fileWrite(std::tm* curTime, std::string funcName, std::string strLog);

private:
    LoggerLibrary();
    static LoggerLibrary* logger;

    bool isOverflow();
    void saveLogFileWithTime();
    std::string getNowFileName();
    void checkOverflowAndSaveFile();
    void changeFileToZip();
    void copyFile(std::string sourceFileName, std::string targetFileName);
};

extern "C" {
    LOGGERLIBRARY_API void logWrite(const char* funcName, const char* strLog);
}
