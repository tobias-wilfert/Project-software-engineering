//
// Created by student on 25.02.19.
//

#include "XmlParser.h"
#include "NullPointer.h"
#include<set>


XmlParser::XmlParser(const char* fileName) {

    TiXmlDocument document;

    if(isValidFile(document, fileName)){
        std::string typeOfFile = checkFileType(document);  // get document type
    }


}




bool XmlParser::isValidFile(TiXmlDocument& file, const char* fileName) {
    //precon
    //postcon
    //checkt of file valid is

    if(!file.LoadFile(fileName)) {
        std::cerr << file.ErrorDesc() << std::endl;
        std::cerr << "Error in document row: "<< file.ErrorRow() << std::endl;
        return false;


    }
    if(file.FirstChildElement() == NULL) { //if root == NULL
        std::cerr << "Failed to load file: No root element." << std::endl;
        file.Clear();
        return false;

    }
    return true;
}

std::string XmlParser::checkFileType(TiXmlDocument &document) {
    TiXmlElement* root = document.FirstChildElement();
    TiXmlElement* brother = root->FirstChildElement()->NextSiblingElement();
    std::set<std::string> attribute;

    for(TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()){
        //CD* cd = new CD();
        //cdPointers.push_back(cd);
        TiXmlElement* currentElement;
        if(elem->GetText() == "VOERTUIG"){}
        if(elem->GetText() == "BAAN"){ // zoek voor verbinding, if verbinding aan
            for(TiXmlElement* elem2 = elem->FirstChildElement(); elem2 != NULL;
                elem2 = elem2->NextSiblingElement()) {
                std::string elemName = elem2->Value();

                const char* attr;
                if(elemName == "verbinding") {
                    if(attr != NULL){
                            attribute.insert("verbinding");
                        }
                        //cout << attr << endl;
                    }; // Do stuff with it
        }
        for(TiXmlElement* elem2 = elem->FirstChildElement(); elem2 != NULL;
            elem2 = elem2->NextSiblingElement()) {
            std::string elemName = elem2->Value();

            const char* attr;
            if(elemName == "ARTIST") {
                if(attr != NULL){
                    //cout << "Artist: " << elem->GetText() << endl;
                    if(elem2->GetText() != NULL){
                        cd->setArtist(elem2->GetText());
                    }
                    //cout << attr << endl;
                }
                ; // Do stuff with it
            }
            else if(elemName == "TITLE") {
                if(attr != NULL){
                    if(elem2->GetText() != NULL){
                        cd->setTitle(elem2->GetText());
                    }
                    //cout << "Title: "<< elem->GetText() << endl;
                    //cout << attr << endl;
                }
                ; // Do stuff with it
            }
            else if(elemName == "COUNTRY") {
                if(attr != NULL){
                    if(elem2->GetText() != NULL){
                        cd->setCountry(elem2->GetText());
                    }
                    //cout << "Title: "<< elem->GetText() << endl;
                    //cout << attr << endl;
                }
                ; // Do stuff with it
            }
            else if(elemName == "COMPANY") {
                if(attr != NULL){
                    if(elem2->GetText() != NULL){
                        cd->setCompany(elem2->GetText());
                    }
                    // cout << "Title: "<< elem->GetText() << endl;
                    //cout << attr << endl;
                }
                ; // Do stuff with it
            }
            else if(elemName == "PRICE") {


                if(attr != NULL){
                    if(elem2->GetText() != NULL) {
                        try {
                            double value = std::stod(elem2->GetText());
                            cd->setPrice(stod(elem2->GetText()));
                            //std::cout << "Converted string to a value of " << value << std::endl;
                        }
                        catch (std::exception &e) {
                            std::cout << "Could not convert string to double" << std::endl;
                        }
                    }

                    //cout << "Title: "<< elem->GetText() << endl;
                    //cout << attr << endl;
                }
                ; // Do stuff with it
            }
            else if(elemName == "YEAR") {
                if(attr != NULL){
                    if(elem2->GetText() != NULL) {
                        try {
                            int value = std::stoi(elem2->GetText());
                            cd->setYear(stoi(elem2->GetText()));
                            //std::cout << "Converted string to a value of " << value << std::endl;
                        }
                        catch (std::exception &e) {
                            std::cout << "Could not convert string to int" << std::endl;
                        }
                    }
                    //cout << "Title: "<< elem->GetText() << endl;
                    //cout << attr << endl;
                }
                ; // Do stuff with it
            }




            else if(elemName == "Element2") {
                attr = elem->Attribute("attribute2");
                if(attr != NULL){
                    cout << attr << endl;
                }
                ; // Do stuff with it
                attr = elem->Attribute("attribute3");
                if(attr != NULL){
                    cout << attr << endl;
                }
                ; // Do stuff with it

                for(TiXmlElement* e = elem->FirstChildElement("Element3"); e != NULL;
                    e = e->NextSiblingElement("Element3")){
                    attr = e->Attribute("attribute4");
                    if(attr != NULL){
                        cout << attr << endl;
                    }
                    ; // Do stuff with it
                }
                for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                    TiXmlText* text = e->ToText();
                    if(text == NULL)
                        continue;
                    string t = text->Value();
                    cout << t << endl;
// Do stuff
                }}

        }
    }

    doc.Clear();

    return fileType;
}


