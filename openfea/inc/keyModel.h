#ifndef KEYMODEL_H
#define KEYMODEL_H

#include "key.h"
#include "keyNode.h"
#include "keyElement.h"
#include "keyPart.h"
#include "keyAssembly.h"
#include "keyInstance.h"
#include "keyMaterial.h"
#include "keyStep.h"

class keyModel : virtual public key {
    protected:
    keyNode nodes;
    keyElement elements;
    std::vector<keyPart> parts;
    keyAssembly assemblies;
    std::vector<keyMaterial> materials;
    std::vector<keyStep> steps;

    matrixInt elemDOF;

    friend class session;

    public:
    keyModel();
    virtual ~keyModel();
    void setParamVal(std::string thisLine);
    void buildModel();
    void print();
};

#endif
