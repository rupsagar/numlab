#ifndef PART_H
#define PART_H

#include "key.h"
#include "keyNode.h"
#include "keyElement.h"
#include "keyNset.h"
#include "keyElset.h"
#include "keySolidSection.h"

class keyPart : virtual public key {
    protected:
    std::vector<keyNode> nodes;
    std::vector<keyElement> elements;
    std::vector<keyNset> nsets;
    std::vector<keyElset> elsets;
    std::vector<keySolidSection> solidsections;

    friend class session;
    friend class keyModel;

    public:
    keyPart();
    virtual ~keyPart();
    void setParamVal(std::string thisLine);
    void print();
};

#endif
