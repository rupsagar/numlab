#include <iostream>
#include <vector>
#include <string>
#include "utility.h"
#include "session.h"

int main() {
    std::string fileName;

    // std::cout << "Enter file name: ";
    // std::cin >> fileName;
    fileName = "./input.txt";
    
    session thisSession;
    thisSession.readInpFile(fileName);
    thisSession.print();

    return 0;
}
