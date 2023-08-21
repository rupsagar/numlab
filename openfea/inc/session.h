#ifndef SESSION_H
#define SESSION_H

#include "keyModel.h"

class session {
    protected:
    std::vector<keyModel> models;

    public:
    session();
    virtual ~session();
    void readInpFile(std::string const &fileName);
    void print();
};

#endif
