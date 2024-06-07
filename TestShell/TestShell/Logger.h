#pragma once

class Logger {
public:
    static Logger* getInstance();
    void write(std::string funcName, std::string strLog);

private:
    static Logger* logger;
    std::string fileName;

    Logger();
    Logger& operator=(const Logger& other) = delete;
    Logger(const Logger& other) = delete;

    static void fileWrite(std::tm* curTime, std::string funcName, std::string strLog);
    static void zipFile(std::string* newFileName);
    static bool isOverflow();
};