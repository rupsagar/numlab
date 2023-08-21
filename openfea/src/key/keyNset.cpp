#include "keyNset.h"

keyNset::keyNset() {
    strKey = "nset";
    blockKey = typeKey({{strKey, "0"}});
    blockParam = typeParam({{"nset", "req", "", "0"}});
    hasData = true;
}

keyNset::~keyNset() {}

void keyNset::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
    
}

void keyNset::setData(std::string &thisDataLine) {
    std::stringstream lineStream(thisDataLine);
    std::string thisData;
    while (std::getline(lineStream, thisData, delimitComma)) {
        id.push_back(stoul(thisData));
    }
}

void keyNset::print() {
    printParam();
    std::cout << std::left << std::setw(10) << strKey << ": ";
    for (unsigned long int i = 0; i < id.size(); i++)
        std::cout << std::setw(10) << id[i];
    std::cout << std::endl;
}
