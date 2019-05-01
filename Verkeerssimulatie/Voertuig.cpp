//============================================================================
// Name        : Voertuig.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 2.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include "Voertuig.h"

Voertuig::Voertuig(): fLengte(0), fPositie(0), fSnelheid(-1), fOldPositie(0), fBaan(""), fType(""), fNummerPlaat(""),
fBaanObject(0), fNextVoertuig(0), fDeleteObject(false), fRijstrook(0), fCurrentZone(NULL){

    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Voertuig::~Voertuig() {

}

double Voertuig::getLengte() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getLengte");
    return fLengte;
}

void Voertuig::setLengte(double lengte) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setLengte");
    REQUIRE(lengte > 0, "Lengte must be a positive double");
    Voertuig::fLengte = lengte;
    ENSURE(getLengte() == fLengte, "setLengte post condition failure");
}

double Voertuig::getPositie() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getPositie");
    return fPositie;
}

void Voertuig::setPositie(int positie) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setPositie");
    REQUIRE(positie >= 0, "Positie must be a positive integer");
    Voertuig::fPositie = positie;
    ENSURE(getPositie() == fPositie, "setPositie post condition failure");
}

double Voertuig::getSnelheid() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getSnelheid");
    return fSnelheid;
}

void Voertuig::setSnelheid(int snelheid) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setSnelheid");
    REQUIRE(snelheid >= 0, "Snelheid must be a positive integer");
    Voertuig::fSnelheid = snelheid;
    ENSURE(getSnelheid() == fSnelheid, "setSnelheid post condition failure");
}

double Voertuig::getOldPositie() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getOldPositie");
    return fOldPositie;
}

void Voertuig::setOldPositie(double oldPositie) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setOldPositie");
    REQUIRE(oldPositie >= 0, "oldPositie must be a positive double");
    Voertuig::fOldPositie = oldPositie;
    ENSURE(getOldPositie() == fOldPositie, "setOldPositie post condition failure");
}

const std::string &Voertuig::getBaan() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getBaan");
    return fBaan;
}

void Voertuig::setBaan(const std::string &baan) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setBaan");
    REQUIRE(baan != "", "Baan must be a non empty string");
    Voertuig::fBaan = baan;
    ENSURE(getBaan() == fBaan, "setBaan post condition failure");
}

const std::string &Voertuig::getType() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getType");
    return fType;
}

void Voertuig::setType(const std::string &type) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setType");
    REQUIRE(type != "", "Type must be a non empty string");
    Voertuig::fType = type;
    ENSURE(getType() == fType, "setType post condition failure");
}

const std::string &Voertuig::getNummerPlaat() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getNummerPlaat");
    return fNummerPlaat;
}

void Voertuig::setNummerPlaat(const std::string &nummerPlaat) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setNummerPlaat");
    REQUIRE(nummerPlaat != "", "NummerPlaat must be a non empty string");
    Voertuig::fNummerPlaat = nummerPlaat;
    ENSURE(getNummerPlaat() == fNummerPlaat, "setNummerPlaat post condition failure");
}

Baan *Voertuig::getBaanObject() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getBaanObject");
    return fBaanObject;
}

void Voertuig::setBaanObject(Baan *baanObject) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setBaanObject");
    Voertuig::fBaanObject = baanObject;
    ENSURE(getBaanObject() == fBaanObject, "setBaanObject post condition failure");
}

Voertuig *Voertuig::getNextVoertuig() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getNextVoertuig");
    return fNextVoertuig;
}

void Voertuig::setNextVoertuig(Voertuig *nextVoertuig) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setNextVoertuig");
    Voertuig::fNextVoertuig = nextVoertuig;
    ENSURE(getNextVoertuig() == fNextVoertuig, "setNextVoertuig post condition failure");
}

bool Voertuig::isDeleteObject() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling isDeleteObject");
    return fDeleteObject;
}

void Voertuig::setDeleteObject(bool deleteObject) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setDeleteObject");
    Voertuig::fDeleteObject = deleteObject;
    ENSURE(isDeleteObject() == fDeleteObject, "setDeleteObject post condition failure");
}

void Voertuig::updatePosition() {

    // Maybe make extra sub classes

    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling updatePosition");

    //Calculate the next position
    fPositie = fSnelheid + fPositie;

    //check if position is out of bounds
    if (fPositie > fBaanObject->getLengte()) {
        if (fBaanObject->getVerbindingObject() != 0) {
            fPositie = fPositie - fBaanObject->getLengte();
            fBaanObject = fBaanObject->getVerbindingObject();
            fBaan = fBaanObject->getNaam();
        } else {
            // Delete voertuig from vector (after the iteration) as it still is needed for the other calulations
            fPositie = 0;
            fDeleteObject = true;
        }
    }
    bool changedZone = false;

    //check if in range of a traffic signal(verkeersteken), if true then adjust accordingly
    //first loop over all the traffic signals to find the current zone
    for(unsigned int i = 0; i < fBaanObject->getFVerkeerstekens().size(); i++){
        Verkeersteken* tempNaam = fBaanObject->getFVerkeerstekens().at(i);
        if(tempNaam->getFPositie() <= fPositie && fPositie< tempNaam->getFEndPositie() && tempNaam->getFType() == "ZONE"){
            if (fCurrentZone != tempNaam){
                changedZone = true;
            }
            fCurrentZone = tempNaam;
            break;
        }
    }
    //the current zone is the zone in which our new position is in (newPos > zone) and is the closest of all zones

    // Calculate the speed
    fSnelheid = fVersnelling + fSnelheid;

    // Double adjust
    if (fSnelheid > fBaanObject->getSnelheidsLimiet() && fCurrentZone == NULL) {
        fSnelheid = fBaanObject->getSnelheidsLimiet();
    } else if (fSnelheid < 0) {
        fSnelheid = 0;
    } else if(fCurrentZone != NULL and fSnelheid > fCurrentZone->getFSnelheidslimiet() and fVersnelling > 0 and !changedZone ){
        fSnelheid = fCurrentZone->getFSnelheidslimiet();
    }


    double dIdeal = 0;
    double dActual = 0;
    fVersnelling = fMaxVersnelling; // Default value

    // Because we don't loop over the cars in an ordered fashion it can be that the car in front already moved
    // So we calculate the position of all cars with the old position of the previous car
    fOldPositie = fPositie;

    // If the next voertuig exists
    if (fNextVoertuig != 0) {
        //calculate delta ideal
        dIdeal = (0.75) * fSnelheid + fNextVoertuig->getLengte() + 2;
        //calculate dActual
        dActual = fNextVoertuig->getOldPositie() - fNextVoertuig->getLengte() - fPositie;
        //Calculate the acceleration
        fVersnelling = 0.5 * (dActual - dIdeal);
    }


    double deceleration = 0;
    // Consider change of speed
    if(fCurrentZone != NULL  and fCurrentZone->getFSnelheidslimiet() < fSnelheid){
        // We need to break

        // Check if we  need to break with max speed
        if (fSnelheid+fMinVersnelling >= fCurrentZone->getFSnelheidslimiet()){
            deceleration = fMinVersnelling;
        }else{
            deceleration = (fCurrentZone->getFSnelheidslimiet()-fSnelheid);
        }
    }

    // Also check normal speed
    if (fCurrentZone == NULL and fSnelheid > fBaanObject->getSnelheidsLimiet()){
        // Check if we  need to break with max speed
        if (fSnelheid-fMinVersnelling >=fBaanObject->getSnelheidsLimiet() ){
            deceleration = fMinVersnelling;
        }else{
            deceleration = (fBaanObject->getSnelheidsLimiet()-fSnelheid);
        }
    }

    // check snelheidslimiet van baan
    if (fSnelheid == fBaanObject->getSnelheidsLimiet()){
        fVersnelling = 0;
    }

    if (deceleration < fVersnelling and deceleration != 0){
        fVersnelling = deceleration;
    }



    // If the acceleration is out of bounds take maximum or minimum value
    if (fVersnelling > fMaxVersnelling) {
        fVersnelling = fMaxVersnelling;
    } else if (fVersnelling < fMinVersnelling) {
        fVersnelling = fMinVersnelling;
    }


    ENSURE(fPositie <= fBaanObject->getLengte(), "updatePosition post condition failure");
    if(fCurrentZone == NULL){
        ENSURE(fSnelheid <= fBaanObject->getSnelheidsLimiet(), "updatePosition post condition failure");
    }
    ENSURE(fVersnelling <= fMaxVersnelling, "updatePosition post condition failure");
    ENSURE(fVersnelling >= fMinVersnelling, "updatePosition post condition failure");
}

Verkeersteken *Voertuig::getFCurrentZone() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getFCurrentZone");
    return fCurrentZone;
}

void Voertuig::setFCurrentZone(Verkeersteken *fCurrentZone) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFCurrentZone");

    Voertuig::fCurrentZone = fCurrentZone;
    ENSURE(getFCurrentZone() == fCurrentZone, "setFCurrentZone post condition failure");
}

const std::vector<Verkeersteken *> &Voertuig::getFPassedVerkeerstekens() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getFPassedVerkeerstekens");
    return fPassedVerkeerstekens;
}

void Voertuig::addFPassedVerkeerstekens(Verkeersteken * fPassedVerkeerstekens) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling addFPassedVerkeerstekens");

    ENSURE(fPassedVerkeerstekens != NULL, "addFPassedVerkeerstekens pre condition failure");
    Voertuig::fPassedVerkeerstekens.push_back(fPassedVerkeerstekens);
    ENSURE(getFPassedVerkeerstekens().back() == fPassedVerkeerstekens, "addFPassedVerkeerstekens post condition failure");
}

double Voertuig::getFVersnelling() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getFVersnelling");

    return fVersnelling;
}

void Voertuig::setFVersnelling(double fVersnelling) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFVersnelling");

    Voertuig::fVersnelling = fVersnelling;
    ENSURE(getFVersnelling() == fVersnelling, "setFVersnelling post condition failure");
}

void Voertuig::setFMaxSnelheid(double fMaxSnelheid) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFMaxSnelheid");

    ENSURE(fMaxSnelheid >= 0, "setFMaxSnelheid pre condition failure" );
    Voertuig::fMaxSnelheid = fMaxSnelheid;
    ENSURE(fMaxSnelheid == Voertuig::fMaxSnelheid, "setFMaxSnelheid post condition failure" );
}

void Voertuig::setFMaxVersnelling(double fMaxVersnelling) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFMaxVersnelling");

    ENSURE(fMaxSnelheid >= 0, "setFMaxVersnelling pre condition failure" );
    Voertuig::fMaxVersnelling = fMaxVersnelling;
    ENSURE(fMaxVersnelling == Voertuig::fMaxVersnelling, "setFMaxSnelheid post condition failure" );
}

void Voertuig::setFMinVersnelling(double fMinVersnelling) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFMinVersnelling");

    ENSURE(fMinVersnelling <= 0, "setFMinVersnelling pre condition failure" );
    Voertuig::fMinVersnelling = fMinVersnelling;
    ENSURE(Voertuig::fMinVersnelling == fMinVersnelling, "setFMinVersnelling post condition failure" );
}

int Voertuig::getFRijstrook() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getFRijstrook");
    return fRijstrook;
}

void Voertuig::setFRijstrook(int fRijstrook) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFRijstrook");

    ENSURE(fRijstrook >= 0, "setFRijstrook pre condition failure");
    Voertuig::fRijstrook = fRijstrook;
    ENSURE(getFRijstrook() == fRijstrook, "setFRijstrook post condition failure");
}

bool Voertuig::properlyInitialized() const{
    return _initCheck == this;
}

void Voertuig::set_initCheck(Voertuig *_initCheck) {
    Voertuig::_initCheck = _initCheck;
}