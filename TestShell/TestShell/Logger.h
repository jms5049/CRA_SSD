#pragma once
class Logger {
public:
    static Logger* getInstance();
    void write(std::string funcName);

private:
    static Logger* logger;
    Logger();
};