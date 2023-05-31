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
    int keyStat[sizeof(key)/sizeof(*key)] = {};
    // int* keyStat = new int[nKey];

    int id; string name;
    string param[2] = {"id", "name"};
    int nParam = sizeof(param)/sizeof(*param);
    int paramStat[sizeof(param)/sizeof(*param)] = {};
    // int* paramStat = new int[nParam];

    public:
    part() {}
    ~part() {}
    string getKey(int i) {
        return key[i-1];
    }
    int getKeyStat(int i) {
        return keyStat[i-1];
    }
    void toggleKeyStat(int i) {
        keyStat[i-1] = !keyStat[i-1];
    }
    string getParam(int i) {
        return param[i-1];
    }
    int getParamStat(int i) {
        return paramStat[i-1];
    }
    void toggleParamStat(int i) {
        paramStat[i-1] = !paramStat[i-1];
    }
    bool needParam() {
        int paramStatSum = 0;
        for(int i=0; i<nParam; i++) {
            paramStatSum = paramStatSum+paramStat[i];
        }
        if(paramStatSum==nParam) return false; 
        else return true;
    }
    void setParamVal(string inpParam, string val) {
        if(inpParam==param[0]) {
            id = stoi(val);
            paramStat[0] = 1;
        } else if(inpParam==param[1]) {
            name = val;
            paramStat[1] = 1;
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
    int* keyStat = new int[nKey];

    int id, dim; string name;
    string param[3] = {"id", "dim", "name"};
    int nParam = sizeof(param)/sizeof(*param);
    int* paramStat = new int[nParam];
    
    vector<part> parts;

    public:
    model() {}
    ~model() {}
    string getKey(int i) {
        return key[i-1];
    }
    int getKeyStat(int i) {
        return keyStat[i-1];
    }
    void toggleKeyStat(int i) {
        keyStat[i-1] = !keyStat[i-1];
    }
    string getParam(int i) {
        return param[i-1];
    }
    int getParamStat(int i) {
        return paramStat[i-1];
    }
    void toggleParamStat(int i) {
        paramStat[i-1] = !paramStat[i-1];
    }
    bool needParam() {
        int paramStatSum = 0;
        for(int i=0; i<nParam; i++) {
            paramStatSum = paramStatSum+paramStat[i];
        }
        if(paramStatSum==nParam) return false; 
        else return true;
    }
    void setParamVal(string inpParam, string val) {
        if(inpParam==param[0]) {
            id = stoi(val);
            paramStat[0] = 1;
        } else if(inpParam==param[1]) {
            dim = stoi(val);
            paramStat[1] = 1;
        } else if(inpParam==param[2]) {
            name = val;
            paramStat[2] = 1;
        }
    }
    void pushPart(part thisPart) {
        parts.push_back(thisPart);
    }
    void printData() {
        cout << "Model: id=" << id << ", dim=" << dim << ", name=" << name <<endl;
        cout << "Contains " << parts.size() << " part(s):" << endl;
        for (int i=0; i<parts.size(); i++) {
            cout << "> Part-" << i+1 << ": ";
            parts[i].printData();
        }
    }
};

class session {
    private:
    vector<model> models;
    string commentStr = "//";

    public:
    void readInputFile(string fileName) {
        ifstream inputFile;
        inputFile.open(fileName);
        if (inputFile.is_open()) {
            model thisModel;
            part thisPart;
            char delimitComma = ',', delimitEqual = '=';
            string thisLine, valComma, valEqual;
            regex delLineSpace("\\n+|\\s+");
            while (getline(inputFile, thisLine)) {
                thisLine = regex_replace(lowerCaseString(thisLine), delLineSpace, "");
                stringstream lineStream1(thisLine);
                while (getline(lineStream1, valComma, delimitComma)) {
                    // model
                    if (valComma==thisModel.getKey(1) & thisModel.getKeyStat(1)==0) {
                        thisModel.toggleKeyStat(1);
                    } else if (thisModel.getKeyStat(1)==1 & thisModel.needParam()) {
                        stringstream lineStream2(valComma);
                        getline(lineStream2, valEqual, delimitEqual);
                        thisModel.setParamVal(valEqual, valComma.substr(valComma.find(delimitEqual) + 1));
                    } else if (valComma==thisModel.getKey(2) & (thisModel.getKeyStat(1)==1 & thisModel.getKeyStat(2)==0)) {
                        thisModel.toggleKeyStat(1);
                        thisModel.toggleKeyStat(2);
                        models.push_back(thisModel);
                        thisModel = model();
                    } else if (valComma==thisModel.getKey(1) & (thisModel.getKeyStat(1)==1 & thisModel.getKeyStat(2)==0)) { 
                        cout << "ERROR! Current model reading not finished but new model is being added." << endl;
                    } 
                    // part
                    if (valComma==thisPart.getKey(1) & thisPart.getKeyStat(1)==0) {
                        thisPart.toggleKeyStat(1);
                    } else if (thisPart.getKeyStat(1)==1 & thisPart.needParam()) {
                        stringstream lineStream2(valComma);
                        getline(lineStream2, valEqual, delimitEqual);
                        // cout <<"inhere";
                        thisPart.setParamVal(valEqual, valComma.substr(valComma.find(delimitEqual) + 1));
                    } else if (valComma==thisPart.getKey(2) & (thisPart.getKeyStat(1)==1 & thisPart.getKeyStat(2)==0)) {
                        thisPart.toggleKeyStat(1);
                        thisPart.toggleKeyStat(2);
                        thisModel.pushPart(thisPart);
                        thisPart = part();
                    } else if (valComma==thisPart.getKey(1) & (thisPart.getKeyStat(1)==1 & thisPart.getKeyStat(2)==0)) { 
                        cout << "ERROR! Current part reading not finished but new part is being added." << endl;
                    }
                }
            }
            models[0].printData();
            inputFile.close();
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
