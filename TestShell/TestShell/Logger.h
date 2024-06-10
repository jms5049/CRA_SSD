#pragma once

class Logger {
public:
    static Logger* getInstance();
    void write(std::string funcName);

private:
    Logger();
    static Logger* logger;
    static string file;
    static void fileWrite(std::tm* curTime, std::string funcName);
    static void zipFile(std::string* newFileName);
    static bool isOverflow();
};