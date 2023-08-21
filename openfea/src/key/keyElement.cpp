#include "keyElement.h"

keyElement::keyElement() {
    strKey = "element";
    blockKey = typeKey({{strKey, "0"}});
    blockParam = typeParam({{"type", "req", "", "0"}, {"elset", "op", "", "0"}});
    hasData = true;
}

keyElement::~keyElement() {}

void keyElement::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (blockParam[0][2] == "t2d2")
            numNode = 2;
        else if (blockParam[0][2] == "b31")
            numNode = 3;
        if (hasData)
            readData = true;
    }
}

void keyElement::setData(std::string &thisDataLine) {
    std::stringstream lineStream(thisDataLine);
    std::string thisData;
    int colCount = 0;
    std::vector<unsigned long int> tempConn;
    while (std::getline(lineStream, thisData, delimitComma)) {
        if (colCount == 0) {
            id.push_back(stoul(thisData));
            if (id.back() == id.size())
                idFlag.push_back(true);
            else
                idFlag.push_back(false);
        } else {
            tempConn.push_back(stoul(thisData));
        }
        colCount++;
    }
    conn.push_back(tempConn);
}

void keyElement::print() {
    printParam();
    for (unsigned long int i = 0; i < id.size(); i++) {
        std::cout << std::left << std::setw(10) << strKey << ": "  << std::setw(10) << id[i];
        for (int j = 0; j < numNode; j++)
            std::cout << std::setw(10) << conn[i][j];
        std::cout << std::endl;
    }
}
