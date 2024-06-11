#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <mutex>


#include "LoggerLibrary.h"

using namespace std;

std::mutex mtx; // 뮤텍스 객체 생성

#if _DEBUG
string filePath = "../../latest.log";
string newFileNameHeader = "../../until_";
#else
string filePath = "./Log/latest.log";
string newFileNameHeader = "./Log/until_";
#endif

static string untilFileName;

LoggerLibrary::LoggerLibrary() {
    untilFileName = "";
    ofstream file(filePath, ios::trunc); // latest.log 초기화
}

LoggerLibrary* LoggerLibrary::logger = nullptr;
LoggerLibrary* getLLInstance() {
    if (LoggerLibrary::logger == nullptr) {
        LoggerLibrary::logger = new LoggerLibrary();
    }
    return LoggerLibrary::logger;
}

void logWrite(LoggerLibrary* loggerLB, const char* funcName, const char* strLog) {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm currentTimeStruct;
    localtime_s(&currentTimeStruct, &currentTime);

    //LoggerLibrary* loggerTS = LoggerLibrary::getInstance();
    loggerLB->fileWrite(&currentTimeStruct, funcName, strLog);
}

void LoggerLibrary::fileWrite(tm* curTime, string funcName, string strLog) {

    checkOverflowAndSaveFile();

    ofstream logFile(filePath, ios::app);
    if (logFile.is_open() == false)  return;

    logFile << "[";
    logFile << put_time(curTime, "%Y.%m.%d %H:%M:%S") << "] ";
    logFile << left << setw(40) << funcName.c_str() << "\t";
    logFile << strLog << endl;
    logFile.close();

}

void LoggerLibrary::checkOverflowAndSaveFile() {
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

bool LoggerLibrary::isOverflow() {
    ifstream logFile(filePath, ios::binary | ios::ate);
    int fileSize = logFile.tellg();
    logFile.close();

    if (fileSize >= (10 * 1024)) return true;
    return false;
}

void LoggerLibrary::copyFile(string sourceFileName, string targetFileName) {
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

void LoggerLibrary::changeFileToZip() {
    string newFileName = untilFileName;
    newFileName = newFileName.erase(newFileName.size() - 4);
    newFileName += ".zip";

    copyFile(untilFileName, newFileName);

    if (DeleteFileA(untilFileName.c_str()) == false) {
        cerr << "Failed to delete file." << endl;
    }
}

void LoggerLibrary::saveLogFileWithTime() {
    string newFileName = newFileNameHeader;
    newFileName += getNowFileName();
    newFileName += ".log";

    copyFile(filePath, newFileName);

    untilFileName = newFileName;
}

string LoggerLibrary::getNowFileName() {
    // 현재 시간 가져오기
    auto now = chrono::system_clock::now();
    time_t nowTime = chrono::system_clock::to_time_t(now);

    // tm 구조체로 변환하여 날짜 및 시간 정보 추출
    tm* localTime = localtime(&nowTime);

    // 년, 월, 일, 시, 분, 초 출력
    string year = to_string(localTime->tm_year + 1900);
    string month = to_string(localTime->tm_mon + 1);
    string day = to_string(localTime->tm_mday);
    string hour = to_string(localTime->tm_hour);
    string minute = to_string(localTime->tm_min);
    string second = to_string(localTime->tm_sec);

    string result = year + month + day + "_" + hour + "h" + "_" + minute + "m" + "_" + second + "s";

    return result;
}