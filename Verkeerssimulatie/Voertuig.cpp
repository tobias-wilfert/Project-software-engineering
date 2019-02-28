//
// Created by yanok on 28/02/2019.
//

#include "Voertuig.h"

Voertuig::Voertuig(const std::string &type, const std::string &nummerPlaat, const std::string &baan, int positie,
                   unsigned int snelheid):

type (type), nummerPlaat(nummerPlaat), baan(baan), positie(positie), snelheid(snelheid) {}

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

int Voertuig::getPositie() const {
    return positie;
}

void Voertuig::setPositie(int positie) {
    Voertuig::positie = positie;
}

int Voertuig::getSnelheid() const {
    return snelheid;
}

void Voertuig::setSnelheid(int snelheid) {
    Voertuig::snelheid = snelheid;
}

Voertuig::Voertuig() {}
