//
// Created by reed on 27.04.19.
//

#include "Verkeersteken.h"

const std::string &Verkeersteken::getFType() const {
    return fType;
}

void Verkeersteken::setFType(const std::string &type) {
    Verkeersteken::fType = type;
}

unsigned int Verkeersteken::getFPositie() const {
    return fPositie;
}

void Verkeersteken::setFPositie(unsigned int positie) {
    Verkeersteken::fPositie = positie;
}

const std::string &Verkeersteken::getFBaan() const {
    return fBaan;
}

void Verkeersteken::setFBaan(const std::string &baan) {
    Verkeersteken::fBaan = baan;
}

int Verkeersteken::getFSnelheidslimiet() const {
    return fSnelheidslimiet;
}

void Verkeersteken::setFSnelheidslimiet(int snelheidslimiet) {
    Verkeersteken::fSnelheidslimiet = snelheidslimiet;
}

unsigned int Verkeersteken::getFEndPositie() const {
    return fEndPositie;
}

void Verkeersteken::setFEndPositie(unsigned int fEndPositie) {
    Verkeersteken::fEndPositie = fEndPositie;
}
