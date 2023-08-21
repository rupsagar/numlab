#ifndef KEYELSET_H
#define KEYELSET_H

#include "key.h"

class keyElset : virtual public key {
    protected:    
    std::vector<unsigned long int> id;

    friend class session;
    friend class keyModel;
    friend class keyPart;
    
    public:
    keyElset();
    virtual ~keyElset();
    void setParamVal(std::string thisLine);
    void setData(std::string &thisDataLine);
    void print();
};

#endif
