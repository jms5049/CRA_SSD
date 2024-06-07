#pragma once
class Logger {
public:
    static Logger* getInstance();
    void write(std::string funcName);

private:
    static Logger* logger;
    std::string filePath;

    Logger();
    Logger& operator=(const Logger& other) = delete;
    Logger(const Logger& other) = delete;

    void fileWrite(std::tm* curTime, std::string funcName);
};