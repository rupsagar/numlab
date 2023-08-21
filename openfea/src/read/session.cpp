#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include "utility.h"
#include "session.h"

session::session() {}

session::~session() {}

void session::readInpFile(std::string const &fileName) {
	std::ifstream inpFile;
	inpFile.open(fileName);
	if (inpFile.is_open()) {
		std::string thisLine, valComma, valEqual;
		std::regex delLineSpace("\\n+||\\s+");
		while (getline(inpFile, thisLine)) {
			thisLine = regex_replace(lowerCaseString(thisLine), delLineSpace, "");
			// check comment
			if (thisLine.substr(0, 2) == strComment)
				continue;
			std::stringstream lineStream(thisLine);
			std::getline(lineStream, valComma, delimitComma);
			// check keyword, data
			if (valComma.substr(0, 1) == strKeyPrefix) {
				if (models.size() > 0) {
					if (models.back().parts.size() > 0) {
						if (models.back().parts.back().nodes.size() > 0) {
							if (models.back().parts.back().nodes.back().readData)
								models.back().parts.back().nodes.back().readData = false;
						}
						if (models.back().parts.back().elements.size() > 0) {
							if (models.back().parts.back().elements.back().readData)
								models.back().parts.back().elements.back().readData = false;
						}
						if (models.back().parts.back().nsets.size() > 0) {
							if (models.back().parts.back().nsets.back().readData)
								models.back().parts.back().nsets.back().readData = false;
						}
						if (models.back().parts.back().elsets.size() > 0) {
							if (models.back().parts.back().elsets.back().readData)
								models.back().parts.back().elsets.back().readData = false;
						}
						if (models.back().parts.back().solidsections.size() > 0) {
							if (models.back().parts.back().solidsections.back().readData)
								models.back().parts.back().solidsections.back().readData = false;
						}
					}
					if (models.back().assemblies.instances.size() > 0) {
						if (models.back().assemblies.instances.back().readData)
							models.back().assemblies.instances.back().readData = false;
					}
					if (models.back().materials.size() > 0) {
						if (models.back().materials.back().elasticProp.readData)
							models.back().materials.back().elasticProp.readData = false;
					}
				}
			}
			// model
			if (valComma == strKeyPrefix+"model" && (models.size() == 0 || (models.size() > 0 && !models.back().needKey()))) {
				models.emplace_back();
				models.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			} else if (models.size() > 0 && valComma == models.back().getKey(1) && models.back().needKey()) {
				models.back().flipKeyFlag(1);
				continue;
			} else if (models.size() > 0 && valComma == models.back().getKey(0) && models.back().needKey()) {
				std::cout << "MODEL: Error! Tried to start new reading without finishing current reading." << std::endl;
				continue;
			}
			// part
			if (valComma == strKeyPrefix+"part" && (models.back().parts.size() == 0 || (models.back().parts.size() > 0 && !models.back().parts.back().needKey()))) {
				models.back().parts.emplace_back();
				models.back().parts.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			} else if (models.back().parts.size() > 0 && valComma == models.back().parts.back().getKey(1) && models.back().parts.back().needKey()) {
				models.back().parts.back().flipKeyFlag(1);				
				continue;
			} else if (models.back().parts.size() > 0 && valComma == models.back().parts.back().getKey(0) && models.back().parts.back().needKey()) {
				std::cout << "PART: Error! Tried to start new reading without finishing current reading." << std::endl;
				continue;
			}
			// node
			if (valComma == strKeyPrefix+"node" && models.back().parts.back().needKey()) {
				models.back().parts.back().nodes.emplace_back();
				models.back().parts.back().nodes.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				if (models.back().parts.back().nodes.back().getParamVal("nset") != "") {
					models.back().parts.back().nsets.emplace_back();
					models.back().parts.back().nsets.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				}
				continue;
			} else if (models.back().parts.back().nodes.size() > 0 && models.back().parts.back().needKey() && models.back().parts.back().nodes.back().needData()) {
				models.back().parts.back().nodes.back().setData(thisLine);
				if (models.back().parts.back().nodes.back().getParamVal("nset") != "")
					models.back().parts.back().nsets.back().setData(valComma);
				continue;
			}
			// element
			if (valComma == strKeyPrefix+"element" && models.back().parts.back().needKey()) {
				models.back().parts.back().elements.emplace_back();
				models.back().parts.back().elements.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				if (models.back().parts.back().elements.back().getParamVal("elset") != "") {
					models.back().parts.back().elsets.emplace_back();
					models.back().parts.back().elsets.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				}
				continue;
			} else if (models.back().parts.back().elements.size() > 0 && models.back().parts.back().needKey() && models.back().parts.back().elements.back().needData()) {
				models.back().parts.back().elements.back().setData(thisLine);
				if (models.back().parts.back().elements.back().getParamVal("elset") != "")
					models.back().parts.back().elsets.back().setData(valComma);
				continue;
			}
			// nset
			if (valComma == strKeyPrefix+"nset" && models.back().parts.back().needKey()) {
				models.back().parts.back().nsets.emplace_back();
				models.back().parts.back().nsets.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			} else if (models.back().parts.back().nsets.size() > 0 && models.back().parts.back().needKey() && models.back().parts.back().nsets.back().needData()) {
				models.back().parts.back().nsets.back().setData(thisLine);
				continue;
			}
			// elset
			if (valComma == strKeyPrefix+"elset" && models.back().parts.back().needKey()) {
				models.back().parts.back().elsets.emplace_back();
				models.back().parts.back().elsets.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			} else if (models.back().parts.back().elsets.size() > 0 && models.back().parts.back().needKey() && models.back().parts.back().elsets.back().needData()) {
				models.back().parts.back().elsets.back().setData(thisLine);
				continue;
			}
			// solid section
			if (valComma == strKeyPrefix+"solidsection" && models.back().parts.back().needKey()) {
				models.back().parts.back().solidsections.emplace_back();
				models.back().parts.back().solidsections.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			} else if (models.back().parts.back().solidsections.size() > 0 && models.back().parts.back().needKey() && models.back().parts.back().solidsections.back().needData()) {
				models.back().parts.back().solidsections.back().setData(thisLine);
				continue;
			}
			// assembly
			if (valComma == strKeyPrefix+"assembly" && !models.back().assemblies.needKey()) {
				models.back().assemblies.setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			} else if (models.back().assemblies.needKey() && valComma == models.back().assemblies.getKey(1)) {
				models.back().assemblies.flipKeyFlag(1);
				continue;
			}
			// instance
			if (valComma == strKeyPrefix+"instance" && (models.back().assemblies.instances.size() == 0 || (models.back().assemblies.instances.size() > 0 && !models.back().assemblies.instances.back().needKey()))) {
				models.back().assemblies.instances.emplace_back();
				models.back().assemblies.instances.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			} else if (models.back().assemblies.instances.size() > 0 && models.back().assemblies.instances.back().needKey() && models.back().assemblies.instances.back().needData()) {
				models.back().assemblies.instances.back().setData(thisLine);
				continue;
			} else if (models.back().assemblies.instances.size() > 0 && valComma == models.back().assemblies.instances.back().getKey(1) && models.back().assemblies.instances.back().needKey()) {
				models.back().assemblies.instances.back().flipKeyFlag(1);
				continue;
			} else if (models.back().assemblies.instances.size() > 0 && valComma == models.back().assemblies.instances.back().getKey(0) && models.back().assemblies.instances.back().needKey()) {
				std::cout << "INSTANCE: Error! Tried to start new reading without finishing current reading." << std::endl;
				continue;
			}
			// material
			if (valComma == strKeyPrefix+"material" && models.back().needKey()) {
				models.back().materials.emplace_back();
				models.back().materials.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			}
			// elastic
			if (valComma == strKeyPrefix+"elastic" && models.back().materials.size() > 0) {
				models.back().materials.back().elasticProp.setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			} else if (models.back().materials.size() > 0 && models.back().materials.back().elasticProp.needData()) {
				models.back().materials.back().elasticProp.setData(thisLine);
				continue;
			}
			// step
			if (valComma == strKeyPrefix+"step" && (models.back().steps.size() == 0 || (models.back().steps.size() > 0 && !models.back().steps.back().needKey()))) {
				models.back().steps.emplace_back();
				models.back().steps.back().setParamVal(thisLine.substr(thisLine.find(delimitComma)+1));
				continue;
			} else if (models.back().steps.size() > 0 && valComma == models.back().steps.back().getKey(1) && models.back().steps.back().needKey()) {
				models.back().steps.back().flipKeyFlag(1);				
				continue;
			} else if (models.back().steps.size() > 0 && valComma == models.back().steps.back().getKey(0) && models.back().steps.back().needKey()) {
				std::cout << "STEP: Error! Tried to start new reading without finishing current reading." << std::endl;
				continue;
			}
		}
		inpFile.close();
		if (models.size() > 0)
			models.back().buildModel();
	} else {
		std::cout << "ERROR! File not found.";
	}
}

void session::print() {
	std::cout << std::left << std::setw(10) << "session" << ": " << "contains " << models.size() << " model(s):" << std::endl;
	for (unsigned long i = 0; i < models.size(); i++)
		models[i].print();
}
