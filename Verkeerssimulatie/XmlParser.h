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

    /// The Name of the File that should be parsed
    const char* fkFileName;

    /// The document that will be parseded
    TiXmlDocument fDocument;

    /// Pointer to vector of pointers to all Banen
    std::vector<Baan*>* fBanen;

    /// Pointer to vector of pointers to all Wegen Netwerken
    std::vector<Baan*>* fWegenNetwerk;

    /// Pointer to vector of pointers to all Voertuigen
    std::vector<Voertuig*>* fVoertuigen;

    /**
    * Parses a file
    * @pre This instance of XmlParser was initialized properly, XmlParser.document is readable
    * @post The file was parsed and the information is from the file is now available to the programme
    */
    void parseFile();

    /**
     * Checks if the file is readable/contains no formatting errors that make the file unparsable
     * @pre This instance of XmlParser was initialized properly
     * @post Will throw an error if the file 'XmlParser.fileName' has xml formatting
     *       errors that are so severe that the file can't be reed by the tinyxmlparser.
     *       Before throwing the error  it will print debugging info.
     * @throw FormattingError
     * @return True if file can be read without problems
     */
    bool isReadable();

    /**
     * Converts a string representation if an int to an int
     * @param string  The string that is to be converted to an integer
     * @pre The string must only contain digits
     * @post If the conversion was succesful,
     *       the integer of string will be returned else an error will be thrown
     * @throw ConversionFailed if string can't be converted to integer
     * @return An integer that consist of the same digits as string
     */
    int stoi(std::string &string) const;

    /**
     * Checks if String is made from only digits
     * @author Lingasamy Sakthivel at https://stackoverflow.com/a/19678719/8076979
     * @param string The string that is to be checked if it only contains digits
     * @pre None
     * @post None
     * @return True if string the string contains only digets else False
     */
    bool is_digits(const std::string &string) const;

    /**
     * Checks if two Constant chars are equal
     * @param cc1 The first of the two const char that will be compared for equality
     * @param cc2 The second of the two const char that will be compared for equality
     * @pre None
     * @pre None
     * @return True if cc1 and cc2 are equal on the length of cc1 + 1 else False
     */
    bool is_equal(const char* cc1, const char* cc2) const;

    ///Use pointer to myself to verify whether I am properly initialized
    XmlParser * _initCheck;

public:

    XmlParser(const char* nameOfFile);

    std::vector<Baan *> *getBanen() const;

    std::vector<Baan *> *getWegenNetwerk() const;

    std::vector<Voertuig *> *getVoertuigen() const;

    //-----------------------------------------
    ///auxiliary routines (private use)
    //-----------------------------------------

    bool properlyInitialized();
};


#endif //DESKTOP_XMLPARSER_H
