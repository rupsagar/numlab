#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <regex>
#include <vector>
#include <set>

using namespace std;

string& lowerCaseString(string &str) {
    for(int i=0;str[i]!='\0';i++) {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
    return str;
}
class node {
    private:
    string key[2] = {"node", "endnode"};
    int nKey = sizeof(key)/sizeof(*key);
    int keyFlag[sizeof(key)/sizeof(*key)] = {};

    int nNode, nNodeRead;
    int* nodes;
    string param[1] = {"number"};
    int nParam = sizeof(param)/sizeof(*param);
    int paramFlag[sizeof(param)/sizeof(*param)] = {};

    public:
    node() {}
    ~node() {}
    string getKey(int i) {
        return key[i-1];
    }
    bool needKey() {
        int keyFlagSum = 0;
        for(int i=0; i<nKey; i++) {
            keyFlagSum = keyFlagSum+keyFlag[i];
        }
        if(keyFlagSum==1 & keyFlagSum<nKey) return true; 
        else return false;
    }
    void flipKeyFlag(int i) {
        keyFlag[i-1] = !keyFlag[i-1];
    }
    string getParam(int i) {
        return param[i-1];
    }
    bool needParam() {
        int paramFlagSum = 0;
        for(int i=0; i<nParam; i++) {
            paramFlagSum = paramFlagSum+paramFlag[i];
        }
        if(paramFlagSum==nParam) return false; 
        else return true;
    }
    void setParamVal(string inpParam, string val) {
        if(inpParam==param[0]) {
            nNode = stoi(val);
            paramFlag[0] = 1;
        }
    }
    bool needData() {
        if (!needParam() & nNodeRead<nNode) return true;
        else return false;
    }
    void printData() {
        cout << " : contains " << nNode << " node(s)" << endl;
    }
};

class part {
    private:
    string key[2] = {"part", "endpart"};
    int nKey = sizeof(key)/sizeof(*key);
    int keyFlag[sizeof(key)/sizeof(*key)] = {};

    int id; string name;
    string param[2] = {"id", "name"};
    int nParam = sizeof(param)/sizeof(*param);
    int paramFlag[sizeof(param)/sizeof(*param)] = {};

    node nodes;
    // element elements;

    public:
    part() {}
    ~part() {}
    string getKey(int i) {
        return key[i-1];
    }
    bool needKey() {
        int keyFlagSum = 0;
        for(int i=0; i<nKey; i++) {
            keyFlagSum = keyFlagSum+keyFlag[i];
        }
        if(keyFlagSum==1 & keyFlagSum<nKey) return true; 
        else return false;
    }
    void flipKeyFlag(int i) {
        keyFlag[i-1] = !keyFlag[i-1];
    }
    string getParam(int i) {
        return param[i-1];
    }
    bool needParam() {
        int paramFlagSum = 0;
        for(int i=0; i<nParam; i++) {
            paramFlagSum = paramFlagSum+paramFlag[i];
        }
        if(paramFlagSum==nParam) return false; 
        else return true;
    }
    void setParamVal(string inpParam, string val) {
        if(inpParam==param[0]) {
            id = stoi(val);
            paramFlag[0] = 1;
        } else if(inpParam==param[1]) {
            name = val;
            paramFlag[1] = 1;
        }
    }
    string getNodeKey(int i) {
        return nodes.getKey(i);
    }
    bool needNodeKey() {
        return nodes.needKey();
    }
    void flipNodeKeyFlag(int i) {
        nodes.flipKeyFlag(i);
    }
    bool needNodeParam() {
        return nodes.needParam();
    }
    void setNodeParam(string inpParam, string val) {
        nodes.setParamVal(inpParam, val);
    }
    bool needNodeData() {
        return nodes.needData();
    }
    void printData(string prompt) {
        cout << prompt << " Part: id=" << id << ", name=" << name;
        nodes.printData();
    }
};

class model {
    private:
    string key[2] = {"model", "endmodel"};
    int nKey = sizeof(key)/sizeof(*key);
    int keyFlag[sizeof(key)/sizeof(*key)] = {};

    int id, dim; string name;
    string param[3] = {"id", "dim", "name"};
    int nParam = sizeof(param)/sizeof(*param);
    int paramFlag[sizeof(param)/sizeof(*param)] = {};
    
    vector<part> parts;
    vector<node> nodes;

    public:
    model() {
        parts.emplace_back();
        nodes.emplace_back();
    }
    ~model() {}
    string getKey(int i) {
        return key[i-1];
    }
    bool needKey() {
        int keyFlagSum = 0;
        for(int i=0; i<nKey; i++) {
            keyFlagSum = keyFlagSum+keyFlag[i];
        }
        if(keyFlagSum==1 & keyFlagSum<nKey) return true; 
        else return false;
    }
    void flipKeyFlag(int i) {
        keyFlag[i-1] = !keyFlag[i-1];
    }
    string getParam(int i) {
        return param[i-1];
    }
    bool needParam() {
        int paramFlagSum = 0;
        for(int i=0; i<nParam; i++) {
            paramFlagSum = paramFlagSum+paramFlag[i];
        }
        if(paramFlagSum==nParam) return false; 
        else return true;
    }
    void setParamVal(string inpParam, string val) {
        if(inpParam==param[0]) {
            id = stoi(val);
            paramFlag[0] = 1;
        } else if(inpParam==param[1]) {
            dim = stoi(val);
            paramFlag[1] = 1;
        } else if(inpParam==param[2]) {
            name = val;
            paramFlag[2] = 1;
        }
    }
    string getPartKey(int i) {
        return parts.back().getKey(i);
    }
    bool needPartKey() {
        return parts.back().needKey();
    }
    void flipPartKeyFlag(int i) {
        parts.back().flipKeyFlag(i);
    }
    bool needPartParam() {
        return parts.back().needParam();
    }
    void setPartParam(string inpParam, string val) {
        parts.back().setParamVal(inpParam, val);
    }
    void initNewPart() {
        parts.emplace_back();
    }
    string getNodeKey(int i) {
        return parts.back().getNodeKey(i);
    }
    bool needNodeKey() {
        return parts.back().needNodeKey();
    }
    void flipNodeKeyFlag(int i) {
        parts.back().flipNodeKeyFlag(i);
    }
    bool needNodeParam() {
        return parts.back().needNodeParam();
    }
    void setNodeParam(string inpParam, string val) {
        parts.back().setNodeParam(inpParam, val);
    }
    bool needNodeData() {
        return parts.back().needNodeData();
    }
    void delLast() {
        parts.pop_back();
        nodes.pop_back();
        for (int i=0; i<parts.size(); i++) {
            // parts[i].delLast();
        }
    }
    void printData(string prompt) {
        string newPrompt = prompt+">";
        cout << prompt << " Model: id=" << id << ", dim=" << dim << ", name=" << name;
        cout <<  " : contains " << parts.size() << " part(s):" << endl;
        for (int i=0; i<parts.size(); i++) {
            parts[i].printData(newPrompt);
        }
    }
};

class session {
    private:
    vector<model> models;
    // vector<analysis> analyses;
    string commentStr = "//";
    char delimitComma = ',', delimitEqual = '=';

    public:
    session() {
        models.emplace_back();
    };
    ~session() {};
    void readInpFile(string fileName) {
        ifstream inpFile;
        inpFile.open(fileName);
        if (inpFile.is_open()) {
            string thisLine, valComma, valEqual;
            regex delLineSpace("\\n+|\\s+");
            while (getline(inpFile, thisLine)) {
                thisLine = regex_replace(lowerCaseString(thisLine), delLineSpace, "");
                stringstream lineStream1(thisLine);
                while (getline(lineStream1, valComma, delimitComma)) {
                    // model
                    if (!models.back().needKey() & valComma==models.back().getKey(1)) {
                        // cout << "in_model_1" <<endl;
                        models.back().flipKeyFlag(1);
                    } else if (models.back().needKey() & models.back().needParam()) {
                        // cout << "in_model_2" <<endl;
                        stringstream lineStream2(valComma);
                        getline(lineStream2, valEqual, delimitEqual);
                        models.back().setParamVal(valEqual, valComma.substr(valComma.find(delimitEqual) + 1));
                    } else if (models.back().needKey() & valComma==models.back().getKey(2)) {
                        // cout << "in_model_3" <<endl;
                        models.back().flipKeyFlag(1);
                        models.back().flipKeyFlag(2);
                        initNewModel();
                    } else if (models.back().needKey() & valComma==models.back().getKey(1)) {
                        // cout << "in_model_4" <<endl;
                        cout << "ERROR! Tried to read new model without ending current model." << endl;
                    } 
                    // part
                    if (!models.back().needPartKey() & valComma==models.back().getPartKey(1)) {
                        models.back().flipPartKeyFlag(1);
                    } else if (models.back().needPartKey() & models.back().needPartParam()) {
                        // cout << "in_part_2" <<endl;
                        stringstream lineStream2(valComma);
                        getline(lineStream2, valEqual, delimitEqual);
                        models.back().setPartParam(valEqual, valComma.substr(valComma.find(delimitEqual) + 1));
                    } else if (models.back().needPartKey() & valComma==models.back().getPartKey(2)) {
                        // cout << "in_part_3" <<endl;
                        models.back().flipPartKeyFlag(1);
                        models.back().flipPartKeyFlag(2);
                        models.back().initNewPart();
                    } else if (models.back().needPartKey() & valComma==models.back().getPartKey(1)) {
                        // cout << "in_part_4" <<endl;
                        cout << "ERROR! Tried to read new part without ending current part." << endl;
                    }
                    // node
                    if (models.back().needPartKey() & (!models.back().needNodeKey()) & valComma==models.back().getNodeKey(1)) {
                        models.back().flipNodeKeyFlag(1);
                    } else if (models.back().needPartKey() & (models.back().needNodeKey() & models.back().needNodeParam())) {
                        stringstream lineStream2(valComma);
                        getline(lineStream2, valEqual, delimitEqual);
                        models.back().setNodeParam(valEqual, valComma.substr(valComma.find(delimitEqual) + 1));
                    } else if (models.back().needPartKey() & (models.back().needNodeKey() & models.back().needNodeData())) {
                        cout << valComma << endl;
                    } 
                    else if (models.back().needPartKey() & (models.back().needNodeKey() & valComma==models.back().getNodeKey(2))) {
                        models.back().flipNodeKeyFlag(1);
                        models.back().flipNodeKeyFlag(2);
                    }
                }
            }
            inpFile.close();
        } else {
            cout << "ERROR! File not found.";
        }
        delLast();
    }
    void initNewModel() {
        models.emplace_back();
    }
    void delLast() {
        models.pop_back();
        for (int i=0; i<models.size(); i++) {
            models[i].delLast();
        }
    }
    void printData(string prompt) {
        string newPrompt = prompt+">";
        cout << "Session: " << "contains " << models.size() << " model(s):" << endl;
        for (int i=0; i<models.size(); i++) {
            models[i].printData(newPrompt);
        }
    }
};

int main() {
    string fileName = "input.txt";
    session thisSession;
    thisSession.readInpFile(fileName);
    thisSession.printData("");
    // cin.get();
    return 0;
}
