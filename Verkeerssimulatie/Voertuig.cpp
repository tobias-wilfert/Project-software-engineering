//
// Created by yanok on 28/02/2019.
//

#include "Voertuig.h"

Voertuig::Voertuig(const std::string &type, const std::string &nummerPlaat, const std::string &baan, double positie,
                   double snelheid):

        positie(positie), snelheid(snelheid), baan(baan), type (type), nummerPlaat(nummerPlaat), nextVoertuig(nullptr98){}

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

const std::string &Voertuig::getBaan() const {
    return baan;
}

void Voertuig::setBaan(const std::string &baan) {
    Voertuig::baan = baan;
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

Voertuig::Voertuig():nextVoertuig(nullptr98) {}



void Voertuig::setNextVoertuig(Voertuig *nextVoertuig) {
    Voertuig::nextVoertuig = nextVoertuig;
}
