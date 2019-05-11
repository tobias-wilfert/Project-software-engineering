//============================================================================
// Name        : XmlParser.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 2.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <cstring>
#include "XmlParser.h"

XmlParser::XmlParser(const char* nameOfFile): fkFileName(nameOfFile) {

    _initCheck = this;

    fVoertuigen = new  std::vector<Voertuig*>;
    fBanen = new  std::vector<Baan*>;
    fWegenNetwerk = new  std::vector<Baan*>;
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
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

std::vector<Baan *> *XmlParser::getBanen() const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling getBanen");
    return fBanen;
}

std::vector<Baan *> *XmlParser::getWegenNetwerk() const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling getWegenNetwerk");
    return fWegenNetwerk;
}

std::vector<Voertuig *> *XmlParser::getVoertuigen() const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling getVoertuigen");
    return fVoertuigen;
}

void XmlParser::parseFile() {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling parseFile");
    REQUIRE(isReadable(), "File to parse must be parse-able");

    // Define the root of the file
    TiXmlElement* root = fDocument.FirstChildElement();

    // Loop over all elements in the most outer scope
    for (TiXmlElement* rootElement = root; rootElement != NULL; rootElement = rootElement->NextSiblingElement()) {

        if (is_equal(rootElement->Value(),"VOERTUIG")) {
            Voertuig *voertuig = new Voertuig();
            voertuig->setFVersnelling(0);
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

                    std::cerr << "Error on line: "<< childOfRootElement->Row() << std::endl;

                    if (is_equal(error, "InvalidValue")) {
                        std::cerr << rootElement->Value() << " his " << childOfRootElement << "->Value() is NULL." << std::endl;
                    } else if (is_equal(error, "InvalidText")) {
                        std::cerr << rootElement->Value() << " his " << childOfRootElement->Value() << " tag is NULL." << std::endl;
                    }
                    //Add a new line to seperate different errors
                    std::cerr << std::endl;
                }

                // Check the value of element Value
                if (elementValue == "type") {
                    voertuig->setType(elementText);
                    if(elementText == "MOTORFIETS"){
                        voertuig->setLengte(1);
                        voertuig->setFMaxSnelheid(180);
                        voertuig->setFMaxVersnelling(4);
                        voertuig->setFMinVersnelling(-10);
                    }
                    else if(elementText == "AUTO"){
                        voertuig->setLengte(3);
                        voertuig->setFMaxSnelheid(150);
                        voertuig->setFMaxVersnelling(2);
                        voertuig->setFMinVersnelling(-8);
                    }
                    else if(elementText == "BUS"){
                        voertuig->setLengte(10);
                        voertuig->setFMaxSnelheid(70);
                        voertuig->setFMaxVersnelling(1);
                        voertuig->setFMinVersnelling(-7);
                    }
                    else if(elementText == "VRACHTWAGEN"){
                        voertuig->setLengte(15);
                        voertuig->setFMaxSnelheid(90);
                        voertuig->setFMaxVersnelling(1);
                        voertuig->setFMinVersnelling(-6);
                    }else{
                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "Unknown type" << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }

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
                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "Can't be converted to a number." << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }

                } else if (elementValue == "snelheid") {
                    try {
                        voertuig->setSnelheid(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "Can't be converted to a number." << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }

                }
            }
            //check if baan nog niet bestaat
            bool geldigVoertuigObject = true;
            for(unsigned int i = 0; i < fVoertuigen->size(); i++){
                if(fVoertuigen->at(i)->getNummerPlaat() == voertuig->getNummerPlaat()){
                    geldigVoertuigObject = false;
                }
            }
            if(geldigVoertuigObject){
                // Add the new instance of 'voertuig' to 'voertuigen'
                fVoertuigen->push_back(voertuig);
            }
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

                    std::cerr << "Error on line: "<< childOfRootElement->Row() << std::endl;

                    if (is_equal(error, "InvalidValue")) {
                        std::cerr << rootElement->Value() << " his " << childOfRootElement << "->Value() is NULL." << std::endl;
                    } else if (is_equal(error, "InvalidText")) {
                        std::cerr << rootElement->Value() << " his " << childOfRootElement->Value() << " tag is NULL." << std::endl;
                    }
                    //Add a new line to seperate different errors
                    std::cerr << std::endl;
                }


                // Check the value of element Value
                if (elementValue == "naam") {
                    baan->setNaam(elementText);

                } else if (elementValue == "snelheidslimiet") {
                    try {
                        baan->setSnelheidsLimiet(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "Can't be converted to a number." << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }


                } else if (elementValue == "lengte") {
                    try {
                        baan->setLengte(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "Can't be converted to a number." << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }

                } else if (elementValue == "verbinding") {
                    isWegenNetwerk = true;
                    baan->setVerbinding(elementText);
                } else if (elementValue == "rijstroken"){
                    try {
                        baan->setFRijstroken(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "Can't be converted to a number." << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }
                }
            }
            bool geldigObject = true;
            if (isWegenNetwerk) {
                //check if wegenNetwerk nog niet bestaat
                for(unsigned int i = 0; i < fWegenNetwerk->size(); i++){
                    if(fWegenNetwerk->at(i)->getNaam() == baan->getNaam()){
                        geldigObject = false;
                    }
                }
                if(geldigObject){
                    // Add the new instance of 'wegenNetwerk' to 'wegenNetwerken'
                    fWegenNetwerk->push_back(baan);
                }
            } else {
                //check if Baan nog niet bestaat
                for(unsigned int i = 0; i < fBanen->size(); i++){
                    if(fBanen->at(i)->getNaam() == baan->getNaam()){
                        geldigObject = false;
                    }
                }
                if(geldigObject){
                    // Add the new instance of 'Baan' to 'Banen'
                    fBanen->push_back(baan);
                }
            }
        }

        //lees verkeersteken
        //een baan gaat een vector van type "verkeersteken" hebben genaamd: "verkeerstekens"
        // dit kan van type "ZONE" en "BUSHALTE" zijn

        ///Todo: vraag, kunnen wij ervanuit gaan dat de baan altijd eerst gegeven wordt voor de verkeersteken?
        ///evt. oplossing, skip if baan niet bestaat

        if (is_equal(rootElement->Value(),"VERKEERSTEKEN")) {
            // Loop over all child elements of rootElement
            Verkeersteken* verkeersteken = new Verkeersteken;
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

                    std::cerr << "Error on line: "<< childOfRootElement->Row() << std::endl;

                    if (is_equal(error, "InvalidValue")) {
                        std::cerr << rootElement->Value() << " his " << childOfRootElement << "->Value() is NULL." << std::endl;
                    } else if (is_equal(error, "InvalidText")) {
                        std::cerr << rootElement->Value() << " his " << childOfRootElement->Value() << " tag is NULL." << std::endl;
                    }
                    //Add a new line to seperate different errors
                    std::cerr << std::endl;

                }
                //we'll split the parsing in two: parsing a BUSHALTE and parsing a ZONE
                // Check the value of element Value
                // type, baan, positie, sneleheidslimiet
                if (elementValue == "type") {
                    if(elementText == "BUSHALTE"){
                        verkeersteken->setFType("BUSHALTE");
                    }
                    else if(elementText == "ZONE"){
                        verkeersteken->setFType("ZONE");
                    }else{
                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "Must either be BUSHALTE or ZONE" << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }
                } else if (elementValue == "snelheidslimiet") {
                    try {
                        verkeersteken->setFSnelheidslimiet(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "Can't be converted to a number." << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }
                } else if (elementValue == "baan") {
                    bool foundBaan = false;
                    //check if baan already exists, otherwise just skip
                    for(unsigned int i = 0; i < fBanen->size(); i++ ){
                        if(fBanen->at(i)->getNaam() == elementText){
                            foundBaan = true;
                        }
                    }
                    for(unsigned int j = 0; j < fWegenNetwerk->size(); j++ ){
                        if(fWegenNetwerk->at(j)->getNaam() == elementText){
                            foundBaan = true;
                        }
                    }
                    if(!foundBaan){
                        // TODO: John what the fuck is this here?
                        //break; //end this loop and move to the next set of values

                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "BAAN needs to declared before VERKEERSTEKEN" << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }
                    //if the baan is found then make sure to add this element to baan
                    verkeersteken->setFBaan(elementText);
                } else if (elementValue == "positie") {
                    try {
                        verkeersteken->setFPositie(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << "Error on line: " << childOfRootElement->Row() << std::endl;
                        std::cerr << "Value of " << childOfRootElement->Value() << ": " << elementText << std::endl;
                        std::cerr << "Can't be converted to a number." << std::endl;
                        //Add a new line to seperate different errors
                        std::cerr << std::endl;
                    }
                }
            }
            //now add the variable to the Baan's "fVerkeerstekens"
            for(unsigned int i = 0; i < fBanen->size(); i++ ){
                if(fBanen->at(i)->getNaam() == verkeersteken->getFBaan()){
                    fBanen->at(i)->addFVerkeersteken(verkeersteken);
                }
            }
            for(unsigned int j = 0; j < fWegenNetwerk->size(); j++ ){
                if(fWegenNetwerk->at(j)->getNaam() == verkeersteken->getFBaan()){
                    fWegenNetwerk->at(j)->addFVerkeersteken(verkeersteken);
                }
            }
        }
    }

    // Close file
    fDocument.Clear();
}

bool XmlParser::isReadable(){
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling isReadable");

    if(!fDocument.LoadFile(fkFileName)) {
        std::cerr << fDocument.ErrorDesc() << std::endl;
        std::cerr << "Error in document row: "<< fDocument.ErrorRow() << std::endl;
        throw "FormattingError";

    }
    if(fDocument.FirstChildElement() == NULL) { //if root == NULL
        std::cerr << "Failed to load file: No root element." << std::endl;
        fDocument.Clear();
        return "FormattingError";

    }
    return true;
}

int XmlParser::stoi(std::string &string) const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling stoi");

    int integer;
    if (is_digits(string)) {
        std::istringstream(string) >> integer;
    } else {
        throw "ConversionFailed";
    }
    return integer;
}

bool XmlParser::is_digits(const std::string &string) const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling is_digits");
    return string.find_first_not_of("0123456789") == std::string::npos;
}

bool XmlParser::is_equal(const char *cc1, const char *cc2) const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling is_equal");
    return 0 == std::strncmp(cc1, cc2, std::strlen(cc1)+1);
}

bool XmlParser::properlyInitialized() const{
    return _initCheck == this;
}

bool XmlParser::compareFiles(const std::string &p1, const std::string &p2) {
    // File compare
    // Source: https://stackoverflow.com/a/37575457/8076979
    std::ifstream f1(p1.c_str(), std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2.c_str(), std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail()) {
        return false; //file problem
    }

    if (f1.tellg() != f2.tellg()) {
        return false; //size mismatch
    }

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}
