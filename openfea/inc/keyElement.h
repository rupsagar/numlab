#ifndef KEYELEMENT_H
#define KEYELEMENT_H

#include "key.h"

class keyElement : virtual public key {
    protected:
    int numNode = 0;
    std::vector<bool> idFlag;
    std::vector<unsigned long int> id;
    matrixUnsignedLongInt conn;

    friend class session;
    friend class keyModel;
    friend class keyPart;

    public:
    keyElement();
    virtual ~keyElement();
    void setParamVal(std::string thisLine);
    void setData(std::string &thisDataLine);
    void print();
};

#endif
