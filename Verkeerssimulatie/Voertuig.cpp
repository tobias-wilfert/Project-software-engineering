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
    double dIdeal;
    double dActual;
    double versnelling;

    fOldPositie = fPositie;

    dIdeal = 0;
    dActual = 0;
    //calculate dIdeal
    if(fNextVoertuig != 0){
        dIdeal = (0.75) * fSnelheid + fNextVoertuig->getLengte() + 2;
    //calculate dActual
        dActual = fNextVoertuig->getOldPositie() - fNextVoertuig->getLengte() - fPositie;
    }

    //calculate acceleration
    versnelling = 0.5*(dActual - dIdeal);
    if(fNextVoertuig == 0){
        versnelling = 2.0;
    }
    // if a out of bounds is then take maximum of minimum bound
    if(versnelling > 2){
        versnelling = 2;
    }
    else if(versnelling < -8){
        versnelling = -8;
    }

    //calculate speed
    //TODO: Consider the speed limit of the baan the car is driving on
    fSnelheid = versnelling + fSnelheid;
    if(fSnelheid > 150){
        fSnelheid = 150.0;
    }
    else if(fSnelheid < 0){
        fSnelheid = 0;
    }
    //calculate  position
    fPositie  = fSnelheid + fPositie;

    if(fPositie > fBaanObject->getLengte()){
        if(fBaanObject->getVerbindingObject() != 0){
            fPositie = fPositie - fBaanObject->getLengte();
            fBaanObject = fBaanObject->getVerbindingObject();
            fBaan = fBaanObject->getNaam();
        }
        else{
            // Delete voertuig from vector (after the iteration)
            fDeleteObject = true;
        }
    }

}
