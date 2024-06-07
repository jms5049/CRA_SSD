#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

#include "Logger.h"

using namespace std;

Logger::Logger() {
    //To-Do:: File Path ?
}

Logger* Logger::logger = nullptr;
 Logger* Logger::getInstance() {
    if (logger == nullptr) {
        logger = new Logger();
    }
    return logger;
}

 void Logger::write(string funcName) {
     auto now = chrono::system_clock::now();
     time_t currentTime = chrono::system_clock::to_time_t(now);
     tm* currentTimeStruct = localtime(&currentTime);

     cout << "[" << put_time(currentTimeStruct, "%Y-%m-%d %H:%M:%S") << "] ";


     cout << left << setw(30) << funcName.c_str() << endl;
 }
