#pragma once

class Logger {
public:
    static Logger* getInstance();
    void write(std::string funcName, std::string strLog);

private:
<<<<<<< HEAD
    Logger();
    static Logger* logger;
    static string file;
    static void fileWrite(std::tm* curTime, std::string funcName);
=======
    static Logger* logger;
    std::string fileName;

    Logger();
    Logger& operator=(const Logger& other) = delete;
    Logger(const Logger& other) = delete;

    static void fileWrite(std::tm* curTime, std::string funcName, std::string strLog);
>>>>>>> aa02a4fbcf27adcd458ac5e4f580e0451a299fc3
    static void zipFile(std::string* newFileName);
    static bool isOverflow();
};