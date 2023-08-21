#include "keyMaterial.h"

keyMaterial::keyMaterial() {
    strKey = "material";
    blockKey = typeKey({{strKey, "0"}});
    blockParam = typeParam({{"name", "req", "", "0"}});
}

keyMaterial::~keyMaterial() {}

void keyMaterial::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keyMaterial::print() {
    printParam();
}
