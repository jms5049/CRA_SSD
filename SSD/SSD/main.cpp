#include "ssd.h"

using std::string;
using std::stoi;
using std::invalid_argument;

int stoiWithException(string target) {
    int intData = -1;

    for (int i = 0; i < target.length(); i++) {
        if (target[i] < '0' || target[i] > '9') return -1;
    }

    try {
        intData = stoi(target);
    }
    catch (invalid_argument& e) {
        return -1;
    }
    return intData;
}

bool isIoParameterValid(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) return false;
    
    int lba = stoiWithException(argv[2]);
    if (lba < 0 || lba > 99)  return false;

    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 0;

    string rwChecker = argv[1];
    int lba = 0;
    Ssd device;

    if (rwChecker != "F") {
        lba = stoiWithException(argv[2]);

        if (isIoParameterValid(argc, argv) == false) return 0;
    }

    if (rwChecker == "W") {
        string hexdata = argv[3];
        if (hexdata.size() != 10 || hexdata[0] != '0' || hexdata[1] != 'x') return 0;
        for (int i = 2; i < 10; i++) {
            if (hexdata[i] >= '0' && hexdata[i] <= '9') continue;
            if (hexdata[i] >= 'A' && hexdata[i] <= 'F') continue;
            return 0;
        }
        device.writeSsd(lba, hexdata);
    }

    if (rwChecker == "R") {
        device.readSsd(lba);
    }

    if (rwChecker == "E") {
        int size = stoiWithException(argv[3]);
        if (size <= 0)  return 0;
        device.eraseSsd(lba, size);
    }

    if (rwChecker == "F") {
        device.flush();
    }
    
    return 0;
}