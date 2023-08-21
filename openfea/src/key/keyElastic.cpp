#include "keyElastic.h"

keyElastic::keyElastic() {
    strKey = "elastic";
    blockKey = typeKey({{strKey, "0"}});
    blockParam = typeParam({{"type", "req", "", "0"}});
    hasData = true;
}

keyElastic::~keyElastic() {}

void keyElastic::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keyElastic::setData(std::string &thisDataLine) {
    std::stringstream lineStream(thisDataLine);
    std::string thisData;
    while (std::getline(lineStream, thisData, delimitComma)) {
        matData.push_back(stod(thisData));
    }
}

void keyElastic::print() {
    printParam();
    std::cout << std::left << std::setw(10) << strKey << ": ";
    for (unsigned long int i = 0; i < matData.size(); i++) {
        std::cout << std::setw(10) << matData[i];
    }
    std::cout << std::endl;
}
