#ifndef KEYASSEMBLY_H
#define KEYASSEMBLY_H

#include "key.h"
#include "keyInstance.h"

class keyAssembly : virtual public key {
    protected:
    std::vector<keyInstance> instances;

    friend class session;
    friend class keyModel;
    friend class keyInstance;

    public:
    keyAssembly();
    virtual ~keyAssembly();
    void setParamVal(std::string thisLine);
    void print();
};

#endif
