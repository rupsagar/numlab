#include "utility.h"

std::string strKeyPrefix = "*";
std::string strComment = "**";
char const delimitComma = ',', delimitEqual = '=';
int nDim = 3;

std::string& lowerCaseString(std::string &str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
    return str;
}

std::string& titleCaseString(std::string &str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (i == 0) {
            if (str[0] >= 'a' && str[0] <= 'z')
                str[0] = str[0] - 32;
        } else {
            if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] = str[i] + 32;
        }  
    }
    return str;
}

void readParamVal(std::vector<pairStrStr> &tempParamVal, std::string paramList) {
    std::stringstream lineStream1(paramList);
    std::string thisBlock, thisParam, thisVal;
    while (std::getline(lineStream1, thisBlock, delimitComma)) {
        std::stringstream lineStream2(thisBlock);
        std::getline(lineStream2, thisParam, delimitEqual);
        thisVal = thisBlock.substr(thisBlock.find(delimitEqual)+1);
        tempParamVal.push_back({thisParam, thisVal});
    }
}
