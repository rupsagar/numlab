#include "key.h"

key::key() {}

key::~key() {}

void key::countParam() {
    for (unsigned long int i = 0; i < blockParam.size(); i++) {
        if (blockParam[i][1] == "op")
            numOpParam++;
        if (blockParam[i][1] == "req")
            numReqParam++;
    }
}

void key::setCon(std::string conStr, int val){
    for (unsigned long int i = 0; i < con.size(); i++) {
        if (con[i].first == conStr)
            con[i].second = val - 1;
    }
}

void key::setDep(std::string depStr, int val){
    for (unsigned long int i = 0; i < dep.size(); i++) {
        if (dep[i].first == depStr)
            dep[i].second.push_back(val-1);
    }
}

std::vector<int> key::getDep(std::string depStr){
    for (unsigned long int i = 0; i < dep.size(); i++) {
        if (dep[i].first == depStr)
            return dep[i].second;
    }
    return std::vector<int>();
}

bool key::needKey() {
    unsigned long int keyFlagSum = 0;
    for (unsigned long int i = 0; i < blockKey.size(); i++) {
        if (blockKey[i][1] == "1")
            keyFlagSum++;
    }
    if (blockKey.size() == 2 && keyFlagSum >= 1 && keyFlagSum < blockKey.size())
        return true;
    else
        return false;
}

std::string key::getKey(int i) {
    return strKeyPrefix+blockKey[i][0];
}

std::string key::getKeyFlag(int i) {
    return blockKey[i][1];
}

void key::flipKeyFlag(std::string &keyStr) {
    for (unsigned long int i = 0; i < blockKey.size(); i++) {
        if (blockKey[i][0] == keyStr) {
            flipKeyFlag(i);
            break;
        }
    }
}

void key::flipKeyFlag(int i) {
    if (blockKey[i][1] == "0")
        blockKey[i][1] = "1";
}

bool key::needParam() {
    int paramFlagSum = 0;
    for (unsigned long int i = 0; i < blockParam.size(); i++) {
        if (blockParam[i][1] == "req" && blockParam[i][3] == "1")
            paramFlagSum++;
    }
    if (paramFlagSum == numReqParam)
        return false; 
    else
        return true;
}

std::string key::getParamVal(std::string paramStr) {
    for (unsigned long int i = 0; i < blockParam.size(); i++) {
        if (blockParam[i][0] == paramStr)
            return blockParam[i][2];
    }
    return std::string("");
}

std::string key::getParam(int i) {
    return blockParam[i][0];
}

void key::readParam(std::string &thisLine) {
    flipKeyFlag(0);
    countParam();
    std::stringstream lineStream1(thisLine);
    std::string thisBlock, thisParam, thisVal;
    while (std::getline(lineStream1, thisBlock, delimitComma)) {
        std::stringstream lineStream2(thisBlock);
        std::getline(lineStream2, thisParam, delimitEqual);
        thisVal = thisBlock.substr(thisBlock.find(delimitEqual)+1);
        setParamStr(thisParam, thisVal);
    }
}

void key::setParamStr(std::string &thisParam, std::string &thisVal) {
    for (unsigned long int i = 0; i < blockParam.size(); i++) {
        if (blockParam[i][0] == thisParam && blockParam[i][3] == "0") {
            blockParam[i][2] = thisVal;
            blockParam[i][3] = "1";
            return;
        }
    }
}

bool key::needData() {
    if (readData && !needParam() && ((blockKey.size() == 1 && blockKey[0][1] == "1") || 
    (blockKey.size() == 2 && blockKey[0][1] == "1" && blockKey[1][1] == "0")))
        return true;
    else
        return false;
}

void key::printParam() {
    std::cout << std::left << std::setw(10) << strKey << ": ";
    for (unsigned long int i = 0; i < blockParam.size(); i++) {
        std::cout << blockParam[i][0] << " = " << blockParam[i][2];
        if (i < blockParam.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}