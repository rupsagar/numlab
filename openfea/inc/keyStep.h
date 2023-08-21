#ifndef KEYSTEP_H
#define KEYSTEP_H

#include "key.h"

class keyStep : virtual public key {
    protected:

    friend class session;
    friend class keyModel;
    
    public:
    keyStep();
    virtual ~keyStep();
    void setParamVal(std::string thisLine);
    void print();
};

#endif
