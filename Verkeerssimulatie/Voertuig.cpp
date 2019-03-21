//
// Created by yanok on 28/02/2019.
//

#include "Voertuig.h"

Voertuig::Voertuig(const std::string &type, const std::string &nummerPlaat, std::string baan, double positie,
                   double snelheid):

        lengte(3.0), oldPositie(positie), positie(positie), snelheid(snelheid), baan(baan), type (type),
        nummerPlaat(nummerPlaat), nextVoertuig(nullptr98), baanObject(nullptr98), deleteObject(false){}

Voertuig::Voertuig(){};

const std::string &Voertuig::getType() const {
    return type;
}

void Voertuig::setType(const std::string &type) {
    Voertuig::type = type;
}

const std::string &Voertuig::getNummerPlaat() const {
    return nummerPlaat;
}

void Voertuig::setNummerPlaat(const std::string &nummerPlaat) {
    Voertuig::nummerPlaat = nummerPlaat;
}


double Voertuig::getPositie() const {
    return positie;
}

void Voertuig::setPositie(int positie) {
    Voertuig::positie = positie;
}

double Voertuig::getSnelheid() const {
    return snelheid;
}

void Voertuig::setSnelheid(int snelheid) {
    Voertuig::snelheid = snelheid;
}




void Voertuig::setNextVoertuig(Voertuig *nextVoertuig) {
    Voertuig::nextVoertuig = nextVoertuig;
}

void Voertuig::updatePosition() {
    double dIdeal;
    double dActual;
    double versnelling;

    oldPositie = positie;

    dIdeal = 0;
    dActual = 0;
    //calculate dIdeal
    if(nextVoertuig != nullptr98){
        dIdeal = (0.75) * snelheid + nextVoertuig->getLengte() + 2;
    //calculate dActual
        dActual = nextVoertuig->getOldPositie() - nextVoertuig->getLengte() - positie;
    }

    //calculate acceleration
    versnelling = 0.5*(dActual - dIdeal);
    if(nextVoertuig == nullptr98){
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
    snelheid = versnelling + snelheid;
    if(snelheid > 150){
        snelheid = 150.0;
    }
    else if(snelheid < 0){
        snelheid = 0;
    }
    //calculate  position
    positie  = snelheid + positie;

    if(positie > baanObject->getLengte()){
        if(baanObject->getVerbindingObject() != nullptr98){
            positie = positie - baanObject->getLengte();
            baanObject = baanObject->getVerbindingObject();
            baan = baanObject->getNaam();
        }
        else{
            // Delete voertuig from vector (after the iteration)
            deleteObject = true;
        }
    }

}

double Voertuig::getLengte() const {
    return lengte;
}

double Voertuig::getOldPositie() const {
    return oldPositie;
}

void Voertuig::setOldPositie(double oldPositie) {
    Voertuig::oldPositie = oldPositie;
}

const std::string &Voertuig::getBaan() const {
    return baan;
}

void Voertuig::setBaan(const std::string &baan) {
    Voertuig::baan = baan;
}

Baan *Voertuig::getBaanObject() const {
    return baanObject;
}

void Voertuig::setBaanObject(Baan *baanObject) {
    Voertuig::baanObject = baanObject;
}

Voertuig::~Voertuig() {

}

bool Voertuig::isDeleteObject() const {
    return deleteObject;
}

void Voertuig::setLengte(double lengte) {
    Voertuig::lengte = lengte;
}

void Voertuig::setDeleteObject(bool deleteObject) {
    Voertuig::deleteObject = deleteObject;
}

