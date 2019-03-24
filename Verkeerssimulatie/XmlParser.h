//============================================================================
// Name        : XmlParser.h
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#ifndef DESKTOP_XMLPARSER_H
#define DESKTOP_XMLPARSER_H

#include <sstream>
#include <iostream>
#include <algorithm>
#include "Baan.h"
#include "tinyxml.h"
#include "Voertuig.h"

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
