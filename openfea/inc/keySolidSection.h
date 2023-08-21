#ifndef KEYSOLIDSECTION_H
#define KEYSOLIDSECTION_H

#include "key.h"

class keySolidSection : virtual public key {
    protected:    
    std::vector<double> secProp;

    friend class session;
    friend class keyModel;
    friend class keyPart;
    
    public:
    keySolidSection();
    virtual ~keySolidSection();
    void setParamVal(std::string thisLine);
    void setData(std::string &thisDataLine);
    void print();
};

#endif
