#include "keyNode.h"

keyNode::keyNode() {
    strKey = "node";
    blockKey = typeKey({{strKey, "0"}});
    blockParam = typeParam({{"nset", "op", "", "0"}});
    hasData = true;
}

keyNode::~keyNode() {}

void keyNode::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keyNode::setData(std::string &thisDataLine) {
    std::stringstream lineStream(thisDataLine);
    std::string thisData;
    int colCount = 0;
    std::vector<double> tempCoord;
    while (std::getline(lineStream, thisData, delimitComma)) {
        if (colCount == 0) {
            id.push_back(stoul(thisData));
            if (id.back() == id.size())
                idFlag.push_back(true);
            else
                idFlag.push_back(false);
        } else {
            tempCoord.push_back(stod(thisData));
        }
        colCount++; 
    }
    if (colCount == 3)
        tempCoord.push_back(0);
    coord.push_back(tempCoord);
}

void keyNode::print() {
    printParam();
    for (unsigned long int i = 0; i < id.size(); i++) {
        std::cout << std::left << std::setw(10) << strKey << ": " << std::setw(10) << id[i];
        for (int j = 0; j < nDim; j++)
            std::cout << std::setw(10) << coord[i][j];
        std::cout << std::endl;
    }
}
