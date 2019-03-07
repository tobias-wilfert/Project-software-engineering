//
// Created by yanok on 28/02/2019.
//

#include "Baan.h"

Baan::Baan() {}

const std::string &Baan::getNaam() const {
    return naam;
}

void Baan::setNaam(const std::string &naam) {
    Baan::naam = naam;
}

double Baan::getLengte() const {
    return lengte;
}

void Baan::setLengte(int lengte) {
    Baan::lengte = lengte;
}

double Baan::getSnelheidsLimiet() const {
    return snelheidsLimiet;
}

void Baan::setSnelheidsLimiet(int snelheidsLimiet) {
    Baan::snelheidsLimiet = snelheidsLimiet;
}

const std::string &Baan::getVerbinding() const {
    return verbinding;
}

void Baan::setVerbinding(const std::string &verbinding) {
    Baan::verbinding = verbinding;
}
