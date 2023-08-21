#ifndef KEYINSTANCE_H
#define KEYINSTANCE_H

#include "key.h"

class keyInstance : virtual public key {
    protected:
    double partTransform[6] = {0, 0, 0, 0, 0, 0};

    friend class session;
    friend class keyModel;

    public:
    keyInstance();
    virtual ~keyInstance();
    void setParamVal(std::string thisLine);
    void setData(std::string &thisDataLine);
    void print();
};

#endif
