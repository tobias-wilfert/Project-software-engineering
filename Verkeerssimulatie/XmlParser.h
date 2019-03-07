//
// Created by student on 25.02.19.
//

#ifndef DESKTOP_XMLPARSER_H
#define DESKTOP_XMLPARSER_H

#include <set>
#include <vector>
#include <string>
#include <sstream>
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
    std::vector<Voertuig*>* voertuigen;
    std::vector<Baan*>* banen;
    std::vector<Baan*>* wegenNetwerk;

public:

    XmlParser(const char* nameOfFile);

    bool isReadable();

    std::string checkFileType();

    void parseFile();

    int stoi(std::string &string) const;

    bool is_digits(const std::string &string) const;

    bool is_equal(const char* cc1, const char* cc2) const;

    std::vector<Voertuig *> *getVoertuigen() const;

    std::vector<Baan *> *getBanen() const;

    std::vector<Baan *> *getWegenNetwerk() const;

};


#endif //DESKTOP_XMLPARSER_H
