#include "Logger.h"

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

void Logger::write() {

}