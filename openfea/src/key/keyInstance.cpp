#include "keyInstance.h"

keyInstance::keyInstance() {
    strKey = "instance";
    blockKey = typeKey({{strKey, "0"}, {"end"+strKey, "0"}});
    blockParam = typeParam({{"name", "req", "", "0"}, {"part", "req", "", "0"}});
    hasData = true;
}

keyInstance::~keyInstance() {}

void keyInstance::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keyInstance::setData(std::string &thisDataLine) {
    std::stringstream lineStream(thisDataLine);
    std::string thisData;
    int colCount = 0;
    while (std::getline(lineStream, thisData, delimitComma)) {
        partTransform[colCount] = stod(thisData);
        colCount++;
    }
}

void keyInstance::print() {
    printParam();
    std::cout << std::left << std::setw(10) << strKey << ": ";
    for (unsigned long int i = 0; i < 6; i++) {
        std::cout << std::setw(10) << partTransform[i];
    }
    std::cout << std::endl;
}
