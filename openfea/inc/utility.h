#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <array>

typedef std::pair<std::string, int> pairStrInt;
typedef std::pair<std::string, std::string> pairStrStr;
typedef std::pair<std::string, std::vector<int>> pairStrVecInt;
typedef std::vector<std::array<std::string, 2>> typeKey;
typedef std::vector<std::array<std::string, 4>> typeParam;
typedef std::vector<std::vector<int>> matrixInt;
typedef std::vector<std::vector<unsigned long int>> matrixUnsignedLongInt;
typedef std::vector<std::vector<double>> matrixDouble;

extern std::string strKeyPrefix;
extern std::string strComment;
extern char const delimitComma, delimitEqual;
extern int nDim;

std::string& lowerCaseString(std::string &str);
std::string& titleCaseString(std::string &str);
void readParamVal(std::vector<pairStrStr> &tempParamVal, std::string paramList) ;

#endif
