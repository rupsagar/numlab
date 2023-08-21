#include "keyModel.h"

keyModel::keyModel() {
    strKey = "model";
    blockKey = typeKey({{strKey, "0"}, {"end"+strKey, "0"}});
    blockParam = typeParam({{"name", "req", "", "0"}, {"flatdeck", "req", "", "0"}});
}

keyModel::~keyModel() {}

void keyModel::setParamVal(std::string thisLine) {
    readParam(thisLine);
    if (!needParam()) {
        if (hasData)
            readData = true;
    }
}

void keyModel::buildModel() {
    unsigned long int idNodeCount = 1;
    for (unsigned long i = 0; i < assemblies.instances.size(); i++) {
        for (unsigned long j = 0; j < parts.size(); j++) {
            if (assemblies.instances[i].getParamVal("part") == parts[j].getParamVal("name")) {
                for (unsigned long int k = 0; k < parts[j].nodes.size(); k++) {
                    for (unsigned long int l = 0; l < parts[j].nodes[k].id.size(); l++) {
                        nodes.id.push_back(idNodeCount);
                        idNodeCount++;
                        nodes.coord.push_back(parts[j].nodes[k].coord[l]);
                    }
                }
            }
        }
    }

    unsigned long int idElemCount = 1;
    for (unsigned long i = 0; i < assemblies.instances.size(); i++) {
        for (unsigned long j = 0; j < parts.size(); j++) {
            if (assemblies.instances[i].getParamVal("part") == parts[j].getParamVal("name")) {
                for (unsigned long int k = 0; k < parts[j].elements.size(); k++) {
                    for (unsigned long int l = 0; l < parts[j].elements[k].id.size(); l++) {
                        elements.id.push_back(idElemCount);
                        idElemCount++;
                        elements.numNode = parts[j].elements[k].numNode;
                        elements.conn.push_back(parts[j].elements[k].conn[l]);
                    }
                }
            }
        }
    }

    std::vector<unsigned long int> tempElemDOF;
    int tempNumDOF;
    for (unsigned long int i = 0; i < elements.conn.size(); i++) {
        for (unsigned long int j = 0; j < elements.conn[i].size(); j++) {
            if (elements.conn[i].size() == 2) {
                tempNumDOF = 2;
                for (int k = 0; k < tempNumDOF; k++) {
                    tempElemDOF.push_back((j+1)*tempNumDOF+k+1);
                }
            }
        }
    }
}

void keyModel::print() {
    printParam();

    for (unsigned long j = 0; j < parts.size(); j++) {
        parts[j].print();
        for (unsigned long int k = 0; k < parts[j].nodes.size(); k++)
            parts[j].nodes[k].print();
        for (unsigned long int k = 0; k < parts[j].elements.size(); k++)
            parts[j].elements[k].print();
        for (unsigned long int k = 0; k < parts[j].nsets.size(); k++)
            parts[j].nsets[k].print();
        for (unsigned long int k = 0; k < parts[j].elsets.size(); k++)
            parts[j].elsets[k].print();
        for (unsigned long int k = 0; k < parts[j].solidsections.size(); k++)
            parts[j].solidsections[k].print();
    }

    assemblies.print();
    for (unsigned long j = 0; j < assemblies.instances.size(); j++) {
        assemblies.instances[j].print();
    }

    for (unsigned long j = 0; j < materials.size(); j++) {
        materials[j].print();
        if (materials[j].elasticProp.getKeyFlag(0) == "1")
            materials[j].elasticProp.print();
    }

    for (unsigned long j = 0; j < steps.size(); j++) {
        steps[j].print();
    }

    for (unsigned long int j = 0; j < nodes.id.size(); j++) {
        std::cout << std::left << std::setw(10) << nodes.strKey << ": " << std::setw(10) << nodes.id[j];
        for (int k = 0; k < nDim; k++)
            std::cout << std::setw(10) << nodes.coord[j][k];
        std::cout << std::endl;
    }

    for (unsigned long int j = 0; j < elements.id.size(); j++) {
        std::cout << std::left << std::setw(10) << elements.strKey << ": " << std::setw(10) << elements.id[j];
        for (int k = 0; k < elements.numNode; k++)
            std::cout << std::setw(10) << elements.conn[j][k];
        std::cout << std::endl;
    }
}
