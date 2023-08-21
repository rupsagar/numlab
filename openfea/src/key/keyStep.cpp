#include "keyStep.h"

keyStep::keyStep() {
    strKey = "step";
    blockKey = typeKey({{strKey, "0"}, {"end"+strKey, "0"}});
    blockParam = typeParam({{"name", "op", "", "0"}, {"nlgeom", "op", "", "0"}});
    hasData = true;
}

keyStep::~keyStep() {}

void keyStep::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keyStep::print() {
    printParam();
}
