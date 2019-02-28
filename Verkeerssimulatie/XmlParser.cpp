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
    for (TiXmlElement* rootElement = root; rootElement != NULL; rootElement = rootElement->NextSiblingElement()){

        // If the type is "VOERTUIG"
        if (rootElement->Value() == VOERTUIG) {
            // Make a new instance of 'voertuig'
            Voertuig* voertuig = new Voertuig();
            // Loop over all child elements of rootElement
            for (TiXmlElement *childOfRootElement = rootElement->FirstChildElement(); childOfRootElement != NULL; childOfRootElement = childOfRootElement->NextSiblingElement()) {
                // Get the value and text
                std::string elementValue = childOfRootElement->Value();
                std::string elementText = childOfRootElement->GetText();

                // Check the value of element Value
                if (elementValue == "type") {
                    // TODO: Add exception handling
                    voertuig->setType(elementText);
                 }
                else if (elementValue == "nummerplaat") {
                    // TODO: Add exception handling
                    voertuig->setNummerPlaat(elementText);
                }
                else if (elementValue == "baan") {
                    // TODO: Add exception handling
                    voertuig->setBaan(elementText);
                }
                else if (elementValue == "positie") {
                    // TODO: Add exception handling
                    voertuig->setPositie(stoi(elementText));
                }
                else if (elementValue == "snelheid") {
                    // TODO: Add exception handling
                    voertuig->setSnelheid(stoi(elementText));
                }
            }
            // Add the new instance of 'voertuig' to 'voertuigen'
            voertuigen.push_back(voertuig);
        }

        // If the type is "BAAN"
        if (rootElement->Value() == BAAN) {
            // Make a new instance of 'Baan'
            Baan* baan = new Baan;
            // Set 'isWegenNetwerk' to false as default
            bool isWegenNetwerk = false;
            // Loop over all child elements of rootElement
            for (TiXmlElement *childOfRootElement = rootElement->FirstChildElement(); childOfRootElement != NULL; childOfRootElement = childOfRootElement->NextSiblingElement()) {
                // Get the value and text
                std::string elementValue = childOfRootElement->Value();
                std::string elementText = childOfRootElement->GetText();

                // Check the value of element Value
                if (elementValue == "naam") {
                    // TODO: Add exception handling
                    baan->setNaam(elementText);
                }
                else if (elementValue == "snelheidslimiet") {
                    // TODO: Add exception handling
                    baan->setSnelheidsLimiet(stoi(elementText));
                }
                else if (elementValue == "lengte") {
                    // TODO: Add exception handling
                    baan->setLengte(stoi(elementText));
                }
                else if (elementValue == "verbinding") {
                    // TODO: Add exception handling
                    // Only wegennetwerk has the child element verbinding
                    isWegenNetwerk = true;
                    baan->setVerbinding(elementText);
                }
            }
            if(isWegenNetwerk){
                wegenNetwerk.push_back(baan);
            }
            else{
                banen.push_back(baan);
            }
        }
    }
}

int XmlParser::stoi(std::string string) {
    int integer;
    std::istringstream(string) >> integer;
    return integer;
}
