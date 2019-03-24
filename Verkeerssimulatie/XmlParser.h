//============================================================================
// Name        : XmlParser.h
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#ifndef DESKTOP_XMLPARSER_H
#define DESKTOP_XMLPARSER_H

#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Baan.h"
#include "tinyxml.h"
#include "Voertuig.h"

class XmlParser {
private:

    const char* fkFileName;

    TiXmlDocument fDocument;

    std::vector<Baan*>* fBanen;

    std::vector<Baan*>* fWegenNetwerk;

    std::vector<Voertuig*>* fVoertuigen;

public:

    XmlParser(const char* nameOfFile);

    std::vector<Baan *> *getBanen() const;

    std::vector<Baan *> *getWegenNetwerk() const;

    std::vector<Voertuig *> *getVoertuigen() const;

    // Method's that aren't getters and setters
    // TODO: Check which need to be public

    void parseFile();

    bool isReadable();

    int stoi(std::string &string) const;

    bool is_digits(const std::string &string) const;

    bool is_equal(const char* cc1, const char* cc2) const;

};


#endif //DESKTOP_XMLPARSER_H
