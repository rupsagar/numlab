#include "keyElset.h"

keyElset::keyElset() {
    strKey = "elset";
    blockKey = typeKey({{strKey, "0"}});
    blockParam = typeParam({{"elset", "req", "", "0"}});
    hasData = true;
}

keyElset::~keyElset() {}

void keyElset::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keyElset::setData(std::string &thisDataLine) {
    std::stringstream lineStream(thisDataLine);
    std::string thisData;
    while (std::getline(lineStream, thisData, delimitComma)) {
        id.push_back(stoul(thisData));
    }
}

void keyElset::print() {
    printParam();
    std::cout << std::left << std::setw(10) << strKey << ": ";
    for (unsigned long int i = 0; i < id.size(); i++)
        std::cout << std::setw(10) << id[i];
    std::cout << std::endl;
}
