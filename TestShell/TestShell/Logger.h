#pragma once
class Logger {
public:
    static Logger* getInstance();
    void write();

private:
    static Logger* logger;
    Logger();
};