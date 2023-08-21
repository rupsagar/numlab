#include "keyAssembly.h"

keyAssembly::keyAssembly() {
    strKey = "assembly";
    blockKey = typeKey({{strKey, "0"}, {"end"+strKey, "0"}});
    blockParam = typeParam({{"name", "req", "", "0"}});
}

keyAssembly::~keyAssembly() {}

void keyAssembly::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keyAssembly::print() {
    printParam();
}
