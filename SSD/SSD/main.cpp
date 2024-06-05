#include "ssd.h"

using std::string;
using std::stoi;
using std::invalid_argument;

int main(int argc, char *argv[]) {
    // guard
    if (argc < 3 || argc > 4) return 0;
    string rwChecker = argv[1];
    int lba = -1;
    try {
       lba = stoi(argv[2]);
    } 
    catch (invalid_argument& e) {
        return 0;
    }
    if (lba < 0 || lba > 99)  return 0;
    
    Ssd device;

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
    
    return 0;
}