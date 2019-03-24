//============================================================================
// Name        : XmlParser.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <cstring>
#include "XmlParser.h"

XmlParser::XmlParser(const char* nameOfFile): fileName(nameOfFile) {
    voertuigen = new  std::vector<Voertuig*>;
    banen = new  std::vector<Baan*>;
    wegenNetwerk = new  std::vector<Baan*>;
    // If file can't be read stop the program
    try {
        isReadable();
    }
    catch (const char* &error){
        std::cerr <<"Program was terminated because of an "<< error <<" thrown by isReadable()"<< std::endl;
        exit(1);
    }

    // Parse the file
    parseFile();

}

bool XmlParser::isReadable(){
    /**
     * @pre This instance of XmlParser was initialized properly
     * @post Will throw an error if the file 'XmlParser.fileName' has xml formatting
     *       errors that are so severe that the file can't be reed by the tinyxmlparser.
     *       Before throwing the error  it will print debugging info.
     * @throw FormattingError
     * @return True if file can be read without problems
     */

    if(!document.LoadFile(fileName)) {
        std::cerr << document.ErrorDesc() << std::endl;
        std::cerr << "Error in document row: "<< document.ErrorRow() << std::endl;
        throw "FormattingError";

    }
    if(document.FirstChildElement() == NULL) { //if root == NULL
        std::cerr << "Failed to load file: No root element." << std::endl;
        document.Clear();
        return "FormattingError";

    }
    return true;
}

std::string XmlParser::checkFileType() {
    /**
     * @pre This instance of XmlParser was initialized properly, XmlParser.document is readable
     * @return Returns the type of XmlParser.document
     */
    return "Wegennetwerk of Wegen en voertuigen";
}

void XmlParser::parseFile() {
    /**
     * @pre This instance of XmlParser was initialized properly, XmlParser.document is readable
     * @post The file was parsed and the information is from the file is now available to the programme
     */

    // Define the root of the file
    TiXmlElement* root = document.FirstChildElement();

    // Loop over all elements in the most outer scope
    for (TiXmlElement* rootElement = root; rootElement != NULL; rootElement = rootElement->NextSiblingElement()) {

        if (is_equal(rootElement->Value(),"VOERTUIG")) {
            Voertuig *voertuig = new Voertuig();
            // Set defaults
            voertuig->setLengte(3.0);


            // Loop over all child elements of rootElement
            for (TiXmlElement *childOfRootElement = rootElement->FirstChildElement();
                 childOfRootElement != NULL; childOfRootElement = childOfRootElement->NextSiblingElement()) {

                // Get the value and text of the element
                std::string elementText;
                std::string elementValue;
                try {
                    if (childOfRootElement->GetText() != NULL) {
                        elementText = childOfRootElement->GetText();
                    } else {
                        throw "InvalidText";
                    }

                    if (childOfRootElement->Value() != NULL) {
                        elementValue = childOfRootElement->Value();
                    } else {
                        throw "InvalidValue";
                    }
                }
                catch (const char* &error) {
                    if (is_equal(error, "InvalidValue")) {
                        std::cerr << childOfRootElement << "->Value() is NULL." << std::endl;
                    } else if (is_equal(error, "InvalidText")) {
                        std::cerr << childOfRootElement->Value() << " tag is NULL." << std::endl;
                    }
                }

                // TODO: Catch all inconsititentiess
                // Check the value of element Value
                if (elementValue == "type") {
                    voertuig->setType(elementText);

                } else if (elementValue == "nummerplaat") {
                    voertuig->setNummerPlaat(elementText);

                } else if (elementValue == "baan") {
                    voertuig->setBaan(elementText);

                } else if (elementValue == "positie") {
                    try {
                        voertuig->setPositie(stoi(elementText));
                        voertuig->setOldPositie(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << elementText << " can't be converted to a number." << std::endl;
                    }

                } else if (elementValue == "snelheid") {
                    try {
                        voertuig->setSnelheid(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << elementText << " can't be converted to a number." << std::endl;
                    }

                }
            }
            // Add the new instance of 'voertuig' to 'voertuigen'
            voertuigen->push_back(voertuig);
        }

        if (is_equal(rootElement->Value(),"BAAN")) {
            Baan *baan = new Baan;

            // Set 'isWegenNetwerk' to false as default
            bool isWegenNetwerk = false;

            // Loop over all child elements of rootElement
            for (TiXmlElement *childOfRootElement = rootElement->FirstChildElement();
                 childOfRootElement != NULL; childOfRootElement = childOfRootElement->NextSiblingElement()) {


                // Get the value and text of the element
                std::string elementText;
                std::string elementValue;
                try {
                    if (childOfRootElement->GetText() != NULL) {
                        elementText = childOfRootElement->GetText();
                    } else {
                        throw "InvalidText";
                    }

                    if (childOfRootElement->Value() != NULL) {
                        elementValue = childOfRootElement->Value();
                    } else {
                        throw "InvalidValue";
                    }
                }
                catch (const char* &error) {
                    if (is_equal(error, "InvalidValue")) {
                        std::cerr << childOfRootElement << "->Value() is NULL." << std::endl;
                    } else if (is_equal(error, "InvalidText")) {
                        std::cerr << childOfRootElement->Value() << " tag is NULL." << std::endl;
                    }
                }


                // Check the value of element Value
                if (elementValue == "naam") {
                    baan->setNaam(elementText);

                } else if (elementValue == "snelheidslimiet") {
                    try {
                        baan->setSnelheidsLimiet(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << elementText << " can't be converted to a number." << std::endl;
                    }


                } else if (elementValue == "lengte") {
                    try {
                        baan->setLengte(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << elementText << " can't be converted to a number." << std::endl;
                    }

                } else if (elementValue == "verbinding") {
                    isWegenNetwerk = true;
                    baan->setVerbinding(elementText);
                }
            }

            if (isWegenNetwerk) {
                wegenNetwerk->push_back(baan);
            } else {
                banen->push_back(baan);
            }
        }
    }

    // Close file
    document.Clear();
}



int XmlParser::stoi(std::string &string) const {
    /**
     * @param string  The string that is to be converted to an integer
     * @pre The string must only contain digits
     * @post If the conversion was succesful,
     *       the integer of string will be returned else an error will be thrown
     * @throw ConversionFailed if string can't be converted to integer
     * @return An integer that consist of the same digits as string
     */

    int integer;
    if (is_digits(string)) {
        std::istringstream(string) >> integer;
    } else {
        throw "ConversionFailed";
    }
    return integer;
}

bool XmlParser::is_digits(const std::string &string) const {
    /**
     * @author Lingasamy Sakthivel at https://stackoverflow.com/a/19678719/8076979
     * @param string The string that is to be checked if it only contains digits
     * @pre None
     * @post None
     * @return True if string the string contains only digets else False
     */
    return string.find_first_not_of("0123456789") == std::string::npos;
}

bool XmlParser::is_equal(const char *cc1, const char *cc2) const {
    /**
     * @param cc1 The first of the two const char that will be compared for equality
     * @param cc2 The second of the two const char that will be compared for equality
     * @pre None
     * @pre None
     * @return True if cc1 and cc2 are equal on the length of cc1 + 1 else False
     */
    return 0 == std::strncmp(cc1, cc2, std::strlen(cc1)+1);
}

std::vector<Voertuig *> *XmlParser::getVoertuigen() const {
    return voertuigen;
}

std::vector<Baan *> *XmlParser::getBanen() const {
    return banen;
}

std::vector<Baan *> *XmlParser::getWegenNetwerk() const {
    return wegenNetwerk;
}
