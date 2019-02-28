//
// Created by yanok on 28/02/2019.
//

#ifndef VERKEERSSIMULATIE_ONGEBRUIKTECODE_H
#define VERKEERSSIMULATIE_ONGEBRUIKTECODE_H

/*
std::string XmlParser::checkFileType() {
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
    }
}
*/
#endif //VERKEERSSIMULATIE_ONGEBRUIKTECODE_H
