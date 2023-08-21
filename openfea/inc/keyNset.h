#ifndef KEYNSET_H
#define KEYNSET_H

#include "key.h"

class keyNset : virtual public key {
    protected:    
    std::vector<unsigned long int> id;

    friend class session;
    friend class keyModel;
    friend class keyPart;
    
    public:
    keyNset();
    virtual ~keyNset();
    void setParamVal(std::string thisLine);
    void setData(std::string &thisDataLine);
    void print();
};

#endif
