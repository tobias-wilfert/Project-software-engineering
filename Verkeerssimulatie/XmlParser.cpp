//
// Created by student on 25.02.19.
//

#include "XmlParser.h"


XmlParser::XmlParser(const char* nameOfFile): fileName(nameOfFile) {

    // If file can't be read stop the program
    if(!isReadable()){ exit(1); };
    // Parse the file
    parseFile();

}


bool XmlParser::isReadable(){
    // TODO: Add documentation
    //precon
    //postcon
    //checkt of file valid is

    if(!document.LoadFile(fileName)) {
        std::cerr << document.ErrorDesc() << std::endl;
        std::cerr << "Error in document row: "<< document.ErrorRow() << std::endl;
        return false;

    }
    if(document.FirstChildElement() == NULL) { //if root == NULL
        std::cerr << "Failed to load file: No root element." << std::endl;
        document.Clear();
        return false;

    }
    return true;
}

std::string XmlParser::checkFileType() {
    /*
    TiXmlElement* root = document.FirstChildElement(); //bepaal de root

    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        //wij gaan ervan uit dat wegen en voertuigen altijd autos hebben en dat wegennetwerk niet
        // en dat wegennetwerk "verbinding" als element heeft
        TiXmlElement *currentElement;
        if (elem->GetText() == "VOERTUIG") {
            return "Wegen en voertuigen";
        }
        if (elem->GetText() == "BAAN") { // zoek voor verbinding, if verbinding aan
            for (TiXmlElement *elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
                std::string elemName = elem2->Value();
                if (elemName == "verbinding") {
                    return "Wegennetwerk";
                }
            }
        }
    }*/
    return "Wegennetwerk of Wegen en voertuigen";
}


void XmlParser::parseFile() {
    // TODO: Add documentation

    // Work around solution
    std::string BAAN = "BAAN";
    std::string VOERTUIG = "VOERTUIG";

    // Define the root of the file
    TiXmlElement* root = document.FirstChildElement();

    // Loop over all elements in the most outer scope
    for (TiXmlElement* rootElement = root; rootElement != NULL; rootElement = rootElement->NextSiblingElement()) {

        // If the type is "VOERTUIG"
        if (is_equal(rootElement->Value(),"VOERTUIG")) {
            // Make a new instance of 'voertuig'
            Voertuig *voertuig = new Voertuig();
            // Loop over all child elements of rootElement
            for (TiXmlElement *childOfRootElement = rootElement->FirstChildElement();
                 childOfRootElement != NULL; childOfRootElement = childOfRootElement->NextSiblingElement()) {


                // Get the value and text
                std::string elementText;
                std::string elementValue;
                try {
                    // Check that the item is not NULL before we assign it.
                    if (childOfRootElement->GetText() != NULL) {
                        elementText = childOfRootElement->GetText();
                    } else {
                        throw "text Invalid";
                    }

                    if (childOfRootElement->Value() != NULL) {
                        elementValue = childOfRootElement->Value();
                    } else {
                        throw "value Invalid";
                    }
                }
                catch (const char* &error) {
                    if (is_equal(error, "value Invalid")) {
                        std::cerr << childOfRootElement << "->Value() is NULL." << std::endl;
                    } else if (is_equal(error, "text Invalid")) {
                        std::cerr << childOfRootElement->Value() << " tag is NULL." << std::endl;
                    }
                }


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
            voertuigen.push_back(voertuig);
        }

        // If the type is "BAAN"
        if (is_equal(rootElement->Value(),"BAAN")) {
            // Make a new instance of 'Baan'
            Baan *baan = new Baan;

            // Set 'isWegenNetwerk' to false as default
            bool isWegenNetwerk = false;

            // Loop over all child elements of rootElement
            for (TiXmlElement *childOfRootElement = rootElement->FirstChildElement();
                 childOfRootElement != NULL; childOfRootElement = childOfRootElement->NextSiblingElement()) {


                // Get the value and text
                std::string elementText;
                std::string elementValue;
                try {
                    // Check that the item is not NULL before we assign it.
                    if (childOfRootElement->GetText() != NULL) {
                        elementText = childOfRootElement->GetText();
                    } else {
                        throw "text Invalid";
                    }

                    if (childOfRootElement->Value() != NULL) {
                        elementValue = childOfRootElement->Value();
                    } else {
                        throw "value Invalid";
                    }
                }
                catch (const char* &error) {
                    if (is_equal(error, "value Invalid")) {
                        std::cerr << childOfRootElement << "->Value() is NULL." << std::endl;
                    } else if (is_equal(error, "text Invalid")) {
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
                wegenNetwerk.push_back(baan);
            } else {
                banen.push_back(baan);
            }
        }
    }

    // TODO: Check Verifeer consitentie van deerkeersituatie ??

    // Close file
    document.Clear();

}

int XmlParser::stoi(std::string string) const {
    /**
     * @param string  The string that is to be converted to an integer
     * @pre The string must only contain digits
     * @post If the conversion was succesful,
     *       the integer of string will be returned else nothing
     * @throw ConversionFailed
     */

    // Check that string contains only numbers
    int integer;
    if (is_digits(string)) {
        std::istringstream(string) >> integer;
    } else {
        throw "ConversionFailed";
    }
    return integer;
}


// Credit https://stackoverflow.com/questions/19678572/how-to-validate-that-there-are-only-digits-in-a-string
bool XmlParser::is_digits(const std::string &str) const {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

bool XmlParser::is_equal(const char *cc1, const char *cc2) const {
    return 0 == std::strncmp(cc1, cc2, std::strlen(cc1));
}
