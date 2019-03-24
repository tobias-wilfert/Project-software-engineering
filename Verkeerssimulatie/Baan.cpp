//============================================================================
// Name        : Baan.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "Baan.h"

Baan::Baan() {
    fVerbindingObject = 0;
}

Baan::~Baan() {

}

const double &Baan::getLengte() const {
    return fLengte;
}

void Baan::setLengte(const double &lengte) {
    Baan::fLengte = lengte;
}

const std::string &Baan::getNaam() const {
    return fNaam;
}

void Baan::setNaam(const std::string &naam) {
    Baan::fNaam = naam;
}

const double &Baan::getSnelheidsLimiet() const {
    return fSnelheidsLimiet;
}

void Baan::setSnelheidsLimiet(const int &snelheidsLimiet) {
    Baan::fSnelheidsLimiet = snelheidsLimiet;
}

const std::string &Baan::getVerbinding() const {
    return fVerbinding;
}

void Baan::setVerbinding(const std::string &verbinding) {
    Baan::fVerbinding = verbinding;
}

Baan *Baan::getVerbindingObject() const {
    return fVerbindingObject;
}

void Baan::setVerbindingObject(Baan *verbinding) {
    Baan::fVerbindingObject = verbinding;
}
