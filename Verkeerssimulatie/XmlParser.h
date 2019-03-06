//
// Created by student on 25.02.19.
//

#ifndef DESKTOP_XMLPARSER_H
#define DESKTOP_XMLPARSER_H

#include <set>
#include <vector>
#include <string>
#include <sstream>      // std::istringstream$
#include <iostream>
#include <algorithm>

#include "Baan.h"
#include "tinyxml.h"
#include "Voertuig.h"
#include "NullPointer.h"


class XmlParser {
private:
    const char* fileName;
    TiXmlDocument document;
    std::string typeOfFile;
    std::vector<Baan*> banen;
    std::vector<Baan*> wegenNetwerk;
    std::vector<Voertuig*> voertuigen;

public:
    XmlParser(const char* nameOfFile);
    bool isReadable();
    std::string checkFileType();
    void parseFile(); //als preconditie moet typeOfFile al bepaald zijn

    int stoi(std::string string) const;
    bool is_digits(const std::string &str) const;
    bool is_equal(const char* cc1, const char* cc2) const;
};


#endif //DESKTOP_XMLPARSER_H
