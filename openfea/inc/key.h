#ifndef KEY_H
#define KEY_H

#include "utility.h"

class key {
    protected:
    std::vector<pairStrInt> con;
    std::vector<pairStrVecInt> dep;
    std::string strKey;
    typeKey blockKey;
    typeParam blockParam;
    int numReqParam = 0, numOpParam = 0;
    bool hasData = false, readData = false;
    
    public:
    key();
    virtual ~key();
    void countParam();
    void setCon(std::string conStr, int val);
    void setDep(std::string depStr, int val);
    std::vector<int> getDep(std::string depStr);
    bool needKey();
    std::string getKey(int i);
    std::string getKeyFlag(int i);
    void flipKeyFlag(std::string &keyStr);
    void flipKeyFlag(int i);
    bool needParam();
    std::string getParamVal(std::string paramStr);
    std::string getParam(int i);
    void readParam(std::string &thisLine);
    void setParamStr(std::string &inpParam, std::string &val);
    bool needData();
    void printParam();
};

#endif
