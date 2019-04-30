//============================================================================
// Name        : Baan.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "Baan.h"


Baan::Baan() {
    _initCheck = this;
    fVerbindingObject = 0;
    fLengte = 0;
    fSnelheidsLimiet = 0;
    fNaam = "";
    fVerbinding = "";
    fVerbindingObject = NULL;

    ENSURE(properlyInitialized(), "Constructor must end in properly initialized state");

}

Baan::~Baan() {
}

const double &Baan::getLengte() const {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getLengte()");

    return fLengte;
}


void Baan::setLengte(const double &lengte) {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setLengte()");

    REQUIRE(lengte > 0, "setLengte() precondition failure");
    Baan::fLengte = lengte;
    ENSURE(getLengte() == fLengte, "setLengte ()post condition failure");
    ENSURE(fLengte > 0, "setLengte() postcondition failure");
}


const std::string &Baan::getNaam() const {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getNaam()");

    return fNaam;
}

void Baan::setNaam(const std::string &naam) {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setNaam()");

    REQUIRE(!naam.empty(), "setNaam() precondition failure");
    Baan::fNaam = naam;
    ENSURE(getNaam() == fNaam, "setNaam() post condition failure");
}

const int &Baan::getSnelheidsLimiet() const {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getSnelheidsLimiet()");

    return fSnelheidsLimiet;
}

void Baan::setSnelheidsLimiet(const int &snelheidsLimiet) {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setSnelheidsLimiet()");

    REQUIRE(snelheidsLimiet > 0, "setSnelheidsLimiet() precondition failure");
    Baan::fSnelheidsLimiet = snelheidsLimiet;
    ENSURE(snelheidsLimiet == fSnelheidsLimiet, "setSnelheidsLimiet() postcondition failure");
}

const std::string &Baan::getVerbinding() const {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getVerbinding");

    return fVerbinding;
}

void Baan::setVerbinding(const std::string &verbinding) {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setVerbinding");

    REQUIRE(verbinding != "", "setVerbinding() precondition failure");
    Baan::fVerbinding = verbinding;
    ENSURE(getVerbinding() == fVerbinding, "setVerbinding() postcondition failure");
}

Baan *Baan::getVerbindingObject() const {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getVerbindingObject()");

    return fVerbindingObject;
}


void Baan::setVerbindingObject(Baan *verbinding) {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setVerbindingObject()");

    REQUIRE(verbinding != NULL, "setVerbindingObject() precondition failure");
    Baan::fVerbindingObject = verbinding;
    ENSURE(fVerbindingObject = getVerbindingObject(), "setVerbindingObject() postcondition failure");
}


bool Baan::properlyInitialized() const{
    return _initCheck == this;
}

const std::vector<Verkeersteken *> &Baan::getFVerkeerstekens() const {
    return fVerkeerstekens;
}
void Baan::addFVerkeersteken(Verkeersteken* verkeersteken) {
    Baan::fVerkeerstekens.push_back(verkeersteken);
}

int Baan::getFRijstroken() const {
    return fRijstroken;
}

void Baan::setFRijstroken(int fRijstroken) {
    Baan::fRijstroken = fRijstroken;
}

void Baan::sortVerkeersteken() {
    while(!isSorted()){
        for(unsigned int i = 0; i < fVerkeerstekens.size(); i++){
            if(i == fVerkeerstekens.size()-1){
                break; //necessary so we don't get errors later by taking the next sign
            }
            Verkeersteken* temp = fVerkeerstekens.at(i);
            if(fVerkeerstekens.at(i)->getFPositie() > fVerkeerstekens.at(i+1)->getFPositie()){
                fVerkeerstekens.at(i) = fVerkeerstekens.at(i+1);
                fVerkeerstekens.at(i+1) = temp;
            }
        }
    }

}

bool Baan::isSorted() {
    for(unsigned int i = 0; i < fVerkeerstekens.size(); i++){
        Verkeersteken* currentSign = fVerkeerstekens.at(i);
        Verkeersteken* nextSign = NULL;
        if(i == fVerkeerstekens.size()-1){
            break;
        }
        else{
            nextSign = fVerkeerstekens.at(i+1);
        }
        //compare
        if(currentSign->getFPositie()>nextSign->getFPositie()){
            return false;
        }
    }
    return true;

}

void Baan::assignZoneLimit() {
    Verkeersteken* currentZone = NULL;
    for(unsigned int i = 0; i < fVerkeerstekens.size(); i++){
        if(fVerkeerstekens.at(i)->getFType() == "ZONE" && currentZone == NULL){
            currentZone = fVerkeerstekens.at(i);
        }
        //if zone and is not same as current zone then this will be the end of the current zone
        if(fVerkeerstekens.at(i)->getFType() == "ZONE" && currentZone != fVerkeerstekens.at(i)){
            currentZone->setFEndPositie(fVerkeerstekens.at(i)->getFPositie());
            currentZone = fVerkeerstekens.at(i);
        }
        if(i == fVerkeerstekens.size()-1){ //als laatste zone is. eindigt het tot op't einde van de baan
            currentZone->setFEndPositie(fLengte);
        }
    }
}

