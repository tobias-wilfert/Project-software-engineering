//============================================================================
// Name        : Voertuig.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "Voertuig.h"

Voertuig::Voertuig(): fLengte(0), fPositie(0), fSnelheid(-1), fOldPositie(0), fBaan(""), fType(""), fNummerPlaat(""),
fBaanObject(0), fNextVoertuig(0), fDeleteObject(false){

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

    //TODO: Change this, to be in the correct order
    // Maybe make extra sub classes

    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling updatePosition");

    //Calculate the position
    fPositie = fSnelheid + fPositie;

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

    // Calculate the speed
    fSnelheid = fVersnelling + fSnelheid;

    if (fSnelheid > fBaanObject->getSnelheidsLimiet()) {
        fSnelheid = fBaanObject->getSnelheidsLimiet();
    } else if (fSnelheid < 0) {
        fSnelheid = 0;
    }


    double dIdeal = 0;
    double dActual = 0;
    double versnelling = 2.0; // Default value

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

    // If the acceleration is out of bounds take maximum or minimum value
    if (fVersnelling > 2) {
        fVersnelling = 2;
    } else if (fVersnelling < -8) {
        fVersnelling = -8;
    }

    ENSURE(fPositie <= fBaanObject->getLengte(), "updatePosition post condition failure");
    ENSURE(fSnelheid <= fBaanObject->getSnelheidsLimiet(), "updatePosition post condition failure");
    ENSURE(versnelling <= 2, "updatePosition post condition failure");
    ENSURE(versnelling >= -8, "updatePosition post condition failure");
}

bool Voertuig::properlyInitialized() const{
    return _initCheck == this;
}

void Voertuig::set_initCheck(Voertuig *_initCheck) {
    Voertuig::_initCheck = _initCheck;
}
