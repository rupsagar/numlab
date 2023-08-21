#ifndef KEYMATERIAL_H
#define KEYMATERIAL_H

#include "key.h"
#include "keyElastic.h"

class keyMaterial : virtual public key {
    protected:
    keyElastic elasticProp;

    friend class session;
    friend class keyModel;
    
    public:
    keyMaterial();
    virtual ~keyMaterial();
    void setParamVal(std::string thisLine);
    void print();
};

#endif
