#include "keySolidSection.h"

keySolidSection::keySolidSection() {
    strKey = "solidsection";
    blockKey = typeKey({{strKey, "0"}});
    blockParam = typeParam({{"elset", "req", "", "0"}, {"material", "req", "", "0"}});
    hasData = true;
}

keySolidSection::~keySolidSection() {}

void keySolidSection::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keySolidSection::setData(std::string &thisDataLine) {
    std::stringstream lineStream(thisDataLine);
    std::string thisData;
    while (std::getline(lineStream, thisData, delimitComma)) {
        secProp.push_back(stod(thisData));
    }
}

void keySolidSection::print() {
    printParam();
    for (unsigned long int i = 0; i < secProp.size(); i++) {
        std::cout << std::left << std::setw(10) << strKey << ": " << std::setw(10) << secProp[i];
        std::cout << std::endl;
    }
}
