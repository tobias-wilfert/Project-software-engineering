//
// Created by student on 25.02.19.
//

#include "XmlParser.h"



XmlParser::XmlParser(const char* nameOfFile) {
    fileName = nameOfFile;
    if(!isReadable()){
        exit(1);
    }; //stopt programma als niet readable

    parseFile();
    //typeOfFile = checkFileType();  // get document type

}




bool XmlParser::isReadable(){
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

void XmlParser::parseFile() {
    TiXmlElement* root = document.FirstChildElement(); //bepaal de root
    std::string BAAN = "BAAN";
    std::string VOERTUIG = "VOERTUIG";

    for (TiXmlElement* elem = root; elem != nullptr; elem = elem->NextSiblingElement()){
        std::string o = elem->Value();
        if (elem->Value() == VOERTUIG) {
            Voertuig* voertuig = new Voertuig();
            for (TiXmlElement *elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
                std::string elemValue = elem2->Value();
                std::string elemText = elem2->GetText();
                if (elemValue == "type") {
                    //if typeid(elemValue) != std:: string
                    //else if nog een ander check
                    //else
                    voertuig->setType(elemText);
                 }
                else if (elemValue == "nummerplaat") {
                    voertuig->setNummerPlaat(elemText);
                }
                else if (elemValue == "baan") {
                    voertuig->setBaan(elemText);
                }
                else if (elemValue == "positie") {
                    voertuig->setPositie(stoi(elemText));
                }
                else if (elemValue == "snelheid") {
                    voertuig->setSnelheid(stoi(elemText));
                }
            }
            voertuigen.push_back(voertuig);
        }
        if (elem->Value() == BAAN) { // zoek voor verbinding, if verbinding aan
            Baan* baan = new Baan;
            bool isWegenNetwerk = false;
            for (TiXmlElement *elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
                std::string elemValue = elem2->Value();
                std::string elemText = elem2->GetText();
                if (elemValue == "naam") {
                    //if typeid(elemValue) != std:: string
                    //else if nog een ander check
                    //else
                    baan->setNaam(elemText);
                }
                else if (elemValue == "snelheidslimiet") {
                    baan->setSnelheidsLimiet(stoi(elemText));
                }
                else if (elemValue == "lengte") {
                    baan->setLengte(stoi(elemText));
                }
                else if (elemValue == "verbinding") {
                    isWegenNetwerk = true;
                    baan->setVerbinding(elemText);
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
    int i;
    std::istringstream(string) >> i;
    return i;
}










