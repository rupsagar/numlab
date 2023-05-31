#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <regex>
#include <vector>

using namespace std;

string& lowerCaseString(string &str) {
    for(int i=0;str[i]!='\0';i++) {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
    return str;
}

class part {
    private:
    string key[2] = {"part", "endpart"};
    int nKey = sizeof(key)/sizeof(*key);
    int keyFlag[sizeof(key)/sizeof(*key)] = {};
    // int* keyFlag = new int[nKey];

    int id; string name;
    string param[2] = {"id", "name"};
    int nParam = sizeof(param)/sizeof(*param);
    int paramFlag[sizeof(param)/sizeof(*param)] = {};
    // int* paramFlag = new int[nParam];

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
    void setParam(string inpParam, string val) {
        if(inpParam==param[0]) {
            id = stoi(val);
            paramFlag[0] = 1;
        } else if(inpParam==param[1]) {
            name = val;
            paramFlag[1] = 1;
        }
    }
    void printData() {
        cout << "id=" << id << ", name=" << name << endl;
    }
};

class model {
    private:
    string key[2] = {"model", "endmodel"};
    int nKey = sizeof(key)/sizeof(*key);
    int* keyFlag = new int[nKey];

    int id, dim; string name;
    string param[3] = {"id", "dim", "name"};
    int nParam = sizeof(param)/sizeof(*param);
    int* paramFlag = new int[nParam];
    
    vector<part> parts;

    public:
    model() {
        parts.emplace_back();
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
    void setParam(string inpParam, string val) {
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
        parts.back().setParam(inpParam, val);
    }
    void initNewPart() {
        parts.emplace_back();
    }
    void printData() {
        cout << "Model: id=" << id << ", dim=" << dim << ", name=" << name <<endl;
        cout << "Contains " << parts.size()-1 << " part(s):" << endl;
        for (int i=0; i<parts.size()-1; i++) {
            cout << "> Part-" << i+1 << ": ";
            parts[i].printData();
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
    void readInputFile(string fileName) {
        ifstream inputFile;
        inputFile.open(fileName);
        if (inputFile.is_open()) {
            string thisLine, valComma, valEqual;
            regex delLineSpace("\\n+|\\s+");
            while (getline(inputFile, thisLine)) {
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
                        models.back().setParam(valEqual, valComma.substr(valComma.find(delimitEqual) + 1));
                    } else if (models.back().needKey() & valComma==models.back().getKey(2)) {
                        // cout << "in_model_3" <<endl;
                        models.back().flipKeyFlag(1);
                        models.back().flipKeyFlag(2);
                    } else if (models.back().needKey() & valComma==models.back().getKey(1)) {
                        // cout << "in_model_4" <<endl;
                        cout << "ERROR! Tried to read new model without ending current model." << endl;
                    } 
                    // part
                    if (!models.back().needPartKey() & valComma==models.back().getPartKey(1)) {
                        // cout << "in_part_1" <<endl;
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
                }
            }
            inputFile.close();
            models[0].printData();
        } else {
            cout << "ERROR! File not found.";
        }
    }
};

int main() {
    string fileName = "input.txt";
    session thisSession;
    thisSession.readInputFile(fileName);
    //cin.get();
    return 0;
}
