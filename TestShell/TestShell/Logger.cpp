#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <windows.h>

#include "Logger.h"

using namespace std;

string filePath = "../../latest.log";
static string untilFileName;

Logger::Logger() {
    untilFileName = "";
    ofstream file(filePath, ios::trunc); // latest.log 초기화
}

Logger* Logger::logger = nullptr;
Logger* Logger::getInstance() {
    if (logger == nullptr) {
        logger = new Logger();
    }
    return logger;
}

void Logger::write(string funcName, string strLog) {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm currentTimeStruct;
    localtime_s(&currentTimeStruct, &currentTime);

    fileWrite(&currentTimeStruct, funcName, strLog);
}

void Logger::fileWrite(tm* curTime, string funcName, string strLog) {
    checkOverflowAndSaveFile();

    ofstream logFile(filePath, ios::app);
    if (logFile.is_open() == false)  return;

    logFile << put_time(curTime, "%Y-%m-%d %H:%M:%S") << " ";
    logFile << left << setw(50) << funcName.c_str() << "\t";
    logFile << strLog << endl;
    logFile.close();
}

void Logger::checkOverflowAndSaveFile() {
    if (isOverflow()) {
        if (untilFileName != "") {
            changeFileToZip();
        }
        saveLogFileWithTime();

        ofstream file(filePath, ios::trunc); // 파일 열기, 기존 내용 삭제

        if (file.is_open()) {
            file.close(); // 파일 닫기
        }
        else {
            cerr << filePath.c_str() << "Failed to open file." << endl;
        }
    }
}

bool Logger::isOverflow() {
    ifstream logFile(filePath, ios::binary | ios::ate);
    int fileSize = logFile.tellg();
    logFile.close();

    if (fileSize >= (10 * 1024)) return true;
    return false;
}

void Logger::copyFile(string sourceFileName, string targetFileName) {
    ifstream sourceFile(sourceFileName, ios::binary); // 현재 파일을 읽기 모드로 열기
    ofstream targetFile(targetFileName, ios::binary); // 새 파일을 쓰기 모드로 열기

    if (sourceFile && targetFile) {
        targetFile << sourceFile.rdbuf(); // 현재 파일의 내용을 새 파일로 복사
        cout << targetFileName.c_str() << "File copied successfully." << endl;
    }
    else {
        cerr << "Failed to open files." << endl;
    }

    sourceFile.close(); // 파일 닫기
    targetFile.close(); // 파일 닫기
}

void Logger::changeFileToZip() {
    string newFileName = untilFileName;
    newFileName = newFileName.erase(newFileName.size() - 4);
    newFileName += ".zip";

    copyFile(untilFileName, newFileName);

    if (DeleteFileA(untilFileName.c_str()) == false) {
        cerr << "Failed to delete file." << endl;
    }
}

void Logger::saveLogFileWithTime() {
    string newFileName = "../../until_";
    newFileName += getNowFileName();
    newFileName += ".log";

    copyFile(filePath, newFileName);

    untilFileName = newFileName;
}

string Logger::getNowFileName() {
    // 현재 시간 가져오기
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    // tm 구조체로 변환하여 날짜 및 시간 정보 추출
    tm* local_time = localtime(&now_time);

    // 년, 월, 일, 시, 분, 초 출력
    string Year = to_string(local_time->tm_year + 1900);
    string Month = to_string(local_time->tm_mon + 1);
    string Day = to_string(local_time->tm_mday);
    string Hour = to_string(local_time->tm_hour);
    string Minute = to_string(local_time->tm_min);
    string Second = to_string(local_time->tm_sec);

    string result = Year + Month + Day + "_" + Hour + "h" + "_" + Minute + "m" + "_" + Second + "s";

    return result;
}