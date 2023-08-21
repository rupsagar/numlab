#ifndef KEYNODE_H
#define KEYNODE_H

#include "key.h"

class keyNode : virtual public key {
    protected:
    std::vector<bool> idFlag;  
    std::vector<unsigned long int> id;
    matrixDouble coord;

    friend class session;
    friend class keyModel;
    friend class keyPart;
    
    public:
    keyNode();
    virtual ~keyNode();
    void setParamVal(std::string thisLine);
    void setData(std::string &thisDataLine);
    void print();
};

#endif
