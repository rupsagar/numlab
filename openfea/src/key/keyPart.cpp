#include "keyPart.h"

keyPart::keyPart() {
    strKey = "part";
    blockKey = typeKey({{strKey, "0"}, {"end"+strKey, "0"}});
    blockParam = typeParam({{"name", "req", "", "0"}});
}

keyPart::~keyPart() {}

void keyPart::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keyPart::print() {
    printParam();
}
