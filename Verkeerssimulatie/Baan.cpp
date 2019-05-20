//============================================================================
// Name        : Baan.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "Baan.h"


Baan::Baan(): fLengte(0), fSnelheidsLimiet(0), fNaam(""), fVerbinding(""), fVerbindingObject(NULL),
fRijstroken(1), fContainsBushalte(false), flastVoertuig(NULL){

    _initCheck = this;
    ENSURE(properlyInitialized(), "Constructor must end in properly initialized state");
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

    ENSURE(fVerbindingObject == getVerbindingObject(), "setVerbindingObject() postcondition failure");
}

int Baan::getFRijstroken() const {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getFRijstroken()");

    return fRijstroken;
}

void Baan::setFRijstroken(int fRijstroken) {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setFRijstroken()");
    REQUIRE(fRijstroken >= 1, "setFRijstroken() precondition failure");

    Baan::fRijstroken = fRijstroken;

    ENSURE(fRijstroken == getFRijstroken(), "setFRijstroken() postcondition failure");
}

void Baan::assignZoneLimit() {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling assignZoneLimit()");

    Verkeersteken* currentZone = NULL;
    for(unsigned int i = 0; i < fVerkeerstekens.size(); i++){
        if(fVerkeerstekens.at(i)->getFType() == "BUSHALTE"){
            fVerkeerstekens.at(i)->setFEndPositie(fVerkeerstekens.at(i)->getFPositie());
        }
        if(fVerkeerstekens.at(i)->getFType() == "ZONE" && currentZone == NULL){
            currentZone = fVerkeerstekens.at(i);
        }
        // If zone and is not same as current zone then this will be the end of the current zone
        if(fVerkeerstekens.at(i)->getFType() == "ZONE" && currentZone != fVerkeerstekens.at(i)){
            currentZone->setFEndPositie(fVerkeerstekens.at(i)->getFPositie());
            currentZone = fVerkeerstekens.at(i);
        }
        // Als laatste zone is. eindigt het tot op't einde van de baan
        if(i == fVerkeerstekens.size()-1 and currentZone != NULL){
            currentZone->setFEndPositie(fLengte);
        }
    }

    for(unsigned int i = 0; i < fVerkeerstekens.size(); i++){
        ENSURE(fVerkeerstekens.at(i)->getFPositie() <= fVerkeerstekens.at(i)->getFEndPositie(),
                "assignZoneLimit post condition failure");
    }

}

bool Baan::isSorted() {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling isSorted()");

    for(unsigned int i = 0; i < fVerkeerstekens.size(); i++){
        Verkeersteken* currentSign = fVerkeerstekens.at(i);
        Verkeersteken* nextSign = NULL;
        if(i == fVerkeerstekens.size()-1){
            break;
        }
        else{
            nextSign = fVerkeerstekens.at(i+1);
        }
        // Compare
        if(currentSign->getFPositie()>nextSign->getFPositie()){
            return false;
        }
    }
    return true;
}

void Baan::sortVerkeersteken() {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling sortVerkeersteken()");

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

void Baan::addFVerkeersteken(Verkeersteken* verkeersteken) {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling addFVerkeersteken()");
    REQUIRE(verkeersteken != NULL, "addFVerkeersteken() precondition failure");

    Baan::fVerkeerstekens.push_back(verkeersteken);

    ENSURE(getFVerkeerstekens().back() == verkeersteken, "addFVerkeersteken() postcondition failure" );
}

const std::vector<Verkeersteken *> &Baan::getFVerkeerstekens() const {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getFVerkeerstekens()");

    return fVerkeerstekens;
}

bool Baan::properlyInitialized() const{
    return _initCheck == this;
}

void Baan::setfContainsBushalte() {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setfContainsBushalte()");

    for(int i = 0; i < fVerkeerstekens.size(); i++){
        if(fVerkeerstekens.at(i)->getFType() == "BUSHALTE"){
            fContainsBushalte = true;
        }
    }
}

const bool Baan::containsBushalte() const {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling containsBushalte()");

    return fContainsBushalte;
}

Voertuig *Baan::getfLastVoertuig() const {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getfLastVoertuig()");

    return flastVoertuig;
}

void Baan::setfLastVoertuig(Voertuig *lastVoertuig) {
    REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setfLastVoertuig()");
    // Sadly we can't bemore specifiec in ourreuires as Voertuig is just a forward decelertion to this point
    Baan::flastVoertuig = lastVoertuig;

    ENSURE(this->getfLastVoertuig() == lastVoertuig, "setfLastVoertuig() postcondition failure" );
}
