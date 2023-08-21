#ifndef KEYELASTIC_H
#define KEYELASTIC_H

#include "key.h"

class keyElastic : virtual public key {
    protected:    
    std::vector<double> matData;

    friend class session;
    friend class keyModel;
    
    public:
    keyElastic();
    virtual ~keyElastic();
    void setParamVal(std::string thisLine);
    void setData(std::string &thisDataLine);
    void print();
};

#endif
