//
// Created by yanok on 28/02/2019.
//

#ifndef VERKEERSSIMULATIE_ONGEBRUIKTECODE_H
#define VERKEERSSIMULATIE_ONGEBRUIKTECODE_H

/*
vector<CD*> cdPointers = {};


TiXmlDocument doc;
if(!doc.LoadFile("cdCatalogError.xml")) {

    std::cerr << doc.ErrorDesc() << std::endl;
    std::cerr << "Error in document row: "<< doc.ErrorRow() << std::endl;

    return 1;
}

TiXmlElement* root = doc.FirstChildElement();
if(root == NULL) {
    std::cerr << "Failed to load file: No root element." << std::endl;
    doc.Clear();
    return 1;
}

TiXmlElement* brother = root->FirstChildElement()->NextSiblingElement();
for(TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()){
    CD* cd = new CD();
    cdPointers.push_back(cd);
    TiXmlElement* currentElement;
    for(TiXmlElement* elem2 = elem->FirstChildElement(); elem2 != NULL;
        elem2 = elem2->NextSiblingElement()) {
        string elemName = elem2->Value();

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
*/

#endif //VERKEERSSIMULATIE_ONGEBRUIKTECODE_H
