//============================================================================
// Name        : Voertuig.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "Voertuig.h"

Voertuig::Voertuig(): fNextVoertuig(0), fDeleteObject(false){}

Voertuig::~Voertuig() {

}

double Voertuig::getLengte() const {
    return fLengte;
}

void Voertuig::setLengte(double lengte) {
    Voertuig::fLengte = lengte;
}

double Voertuig::getPositie() const {
    return fPositie;
}

void Voertuig::setPositie(int positie) {
    Voertuig::fPositie = positie;
}

double Voertuig::getSnelheid() const {
    return fSnelheid;
}

void Voertuig::setSnelheid(int snelheid) {
    Voertuig::fSnelheid = snelheid;
}

double Voertuig::getOldPositie() const {
    return fOldPositie;
}

void Voertuig::setOldPositie(double oldPositie) {
    Voertuig::fOldPositie = oldPositie;
}

const std::string &Voertuig::getBaan() const {
    return fBaan;
}

void Voertuig::setBaan(const std::string &baan) {
    Voertuig::fBaan = baan;
}

const std::string &Voertuig::getType() const {
    return fType;
}

void Voertuig::setType(const std::string &type) {
    Voertuig::fType = type;
}

const std::string &Voertuig::getNummerPlaat() const {
    return fNummerPlaat;
}

void Voertuig::setNummerPlaat(const std::string &nummerPlaat) {
    Voertuig::fNummerPlaat = nummerPlaat;
}

Baan *Voertuig::getBaanObject() const {
    return fBaanObject;
}

void Voertuig::setBaanObject(Baan *baanObject) {
    Voertuig::fBaanObject = baanObject;
}

Voertuig *Voertuig::getFNextVoertuig() const {
    return fNextVoertuig;
}

void Voertuig::setNextVoertuig(Voertuig *nextVoertuig) {
    Voertuig::fNextVoertuig = nextVoertuig;
}

bool Voertuig::isDeleteObject() const {
    return fDeleteObject;
}

void Voertuig::setDeleteObject(bool deleteObject) {
    Voertuig::fDeleteObject = deleteObject;
}


void Voertuig::updatePosition() {
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
        versnelling = 0.5 * (dActual - dIdeal);
    }

    // If the acceleration is out of bounds take maximum or minimum value
    if (versnelling > 2) {
        versnelling = 2;
    } else if (versnelling < -8) {
        versnelling = -8;
    }

    // Calculate the speed
    fSnelheid = versnelling + fSnelheid;

    if (fSnelheid > fBaanObject->getSnelheidsLimiet()) {
        fSnelheid = fBaanObject->getSnelheidsLimiet();
    } else if (fSnelheid < 0) {
        fSnelheid = 0;
    }

    //Calculate the position
    fPositie = fSnelheid + fPositie;

    if (fPositie > fBaanObject->getLengte()) {
        if (fBaanObject->getVerbindingObject() != 0) {
            fPositie = fPositie - fBaanObject->getLengte();
            fBaanObject = fBaanObject->getVerbindingObject();
            fBaan = fBaanObject->getNaam();
        } else {
            // Delete voertuig from vector (after the iteration) as it still is needed for the other calulations
            fDeleteObject = true;
        }
    }
}
