//============================================================================
// Name        : Baan.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "Baan.h"

Baan::Baan() {
    verbindingObject = 0;
}

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

Baan *Baan::getVerbindingObject() const {
    return verbindingObject;
}

void Baan::setVerbindingObject(Baan *verbinding) {
    Baan::verbindingObject = verbinding;
}

Baan::~Baan() {

}

const std::string &Baan::getVerbinding() const {
    return verbinding;
}

void Baan::setVerbinding(const std::string &verbinding) {
    Baan::verbinding = verbinding;
}

