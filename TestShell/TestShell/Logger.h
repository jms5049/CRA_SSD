#pragma once
class Logger {
public:
    static Logger& get() {
        static Logger logger;
        return logger;
    }

    void write();

private:

    Logger() {}
    ~Logger() {}
    Logger& operator=(const Logger& other) = delete;
    Logger(const Logger& other) = delete;
};