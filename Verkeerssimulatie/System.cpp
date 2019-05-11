//============================================================================
// Name        : System.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 2.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "System.h"
#include <string>
#include <sstream>
#include <algorithm>

template <typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}



System::System(std::vector<Baan *> *Banen, std::vector<Baan *> *WegenNetwerk, std::vector<Voertuig *> *Voertuigen)
        : fBanen(Banen), fWegenNetwerk(WegenNetwerk), fVoertuigen(Voertuigen) {
    _initCheck = this;
    //TODO ENSRURE
    for(int j = 0; j < fBanen->size(); j++){
        fBanen->at(j)->setfContainsBushalte();
    }

    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

std::vector<Baan *> *System::getBanen() const {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling getBanen");
    return fBanen;
}

void System::setBanen(std::vector<Baan *> *Banen) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling setBanen");
    System::fBanen = Banen;
    ENSURE(getBanen() == fBanen, "setBanen post condition failure");
}

std::vector<Baan *> *System::getWegenNetwerk() const {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling getWegenNetwerk");
    return fWegenNetwerk;
}

void System::setWegenNetwerk(std::vector<Baan *> *WegenNetwerk) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling setWegenNetwerk");
    System::fWegenNetwerk = WegenNetwerk;
    ENSURE(getWegenNetwerk() == fWegenNetwerk, "setWegenNetwerk post condition failure");
}

std::vector<Voertuig *> *System::getVoertuigen() const {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling getVoertuigen");
    return fVoertuigen;
}

void System::setVoertuigen(std::vector<Voertuig *> *Voertuigen) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling setVoertuigen");
    System::fVoertuigen = Voertuigen;
    ENSURE(getVoertuigen() == fVoertuigen, "setVoertuigen post condition failure");
}

void System::organizeVehicles() {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling organizeVehicles");

    for(unsigned int i = 0; i<fVoertuigen->size(); i++){
        Voertuig* tempNextVoertuig = 0;
        bool isFirst = true;
        for(unsigned int j = 0; j<fVoertuigen->size(); j++){
            if(j == i){
                continue;
            }
            else if(fVoertuigen->at(j)->getBaan() == fVoertuigen->at(i)->getBaan()){ //check of auto op dezelfde baan zit
                //check of dat de auto voor onze voertuig zit
                if(fVoertuigen->at(j)->getPositie()-fVoertuigen->at(i)->getPositie()>0){
                    if(isFirst){ //als wij een auto gevonden hebben en als de tempNextVoertuig nog geen waarde heeft
                        tempNextVoertuig = fVoertuigen->at(j);
                        isFirst = false;
                    }
                    else if(tempNextVoertuig->getPositie()>fVoertuigen->at(j)->getPositie()){
                        tempNextVoertuig = fVoertuigen->at(j);
                    }
                }
            }
        }
        fVoertuigen->at(i)->setNextVoertuig(tempNextVoertuig);
    }
}

void System::initializeVehicleBaanObject() {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling initializeVehicleBaanObject");

    for(unsigned int i = 0; i < fVoertuigen->size(); i++){
        bool found = false;
        std::string currentVehicleWay = fVoertuigen->at(i)->getBaan();
        for(unsigned int j = 0; j < fBanen->size(); j++){
            if(currentVehicleWay == fBanen->at(j)->getNaam()){
                fVoertuigen->at(i)->setBaanObject(fBanen->at(j));
                found = true;
            }
        }
        if(!found){
            for(unsigned int j = 0; j < fWegenNetwerk->size(); j++){
                if(currentVehicleWay == fWegenNetwerk->at(j)->getNaam()){
                    fVoertuigen->at(i)->setBaanObject(fWegenNetwerk->at(j));
                }
            }
        }
    }
}

void System::initializeBaanVerbindingObjects() {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling initializeBaanVerbindingObjects");


    for(unsigned int i = 0; i < fWegenNetwerk->size(); i++){
        bool found = false;
        std::string currentWay = fWegenNetwerk->at(i)->getVerbinding();
        for(unsigned int j = 0; j < fBanen->size(); j++){
            if(currentWay == fBanen->at(j)->getNaam()){
                fWegenNetwerk->at(i)->setVerbindingObject(fBanen->at(j));
                found = true;
            }
        }
        if(!found){
            for(unsigned int j = 0; j < fWegenNetwerk->size(); j++){
                if(currentWay == fWegenNetwerk->at(j)->getNaam()){
                    fWegenNetwerk->at(i)->setVerbindingObject(fWegenNetwerk->at(j));
                }
            }
        }
    }

}

void System::filterVehicles() {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling filterVehicles");

    std::vector<Voertuig*>* tempVoertuigen = new std::vector<Voertuig*>;

    if(fVoertuigen->size() > 0){
        for(unsigned int i = 0; i < fVoertuigen->size(); i++){
            if(!fVoertuigen->at(i)->isDeleteObject()){//if vehicle is not to be deleted then place this to a vector
                tempVoertuigen->push_back(fVoertuigen->at(i));
            }
        }
        for(unsigned long j = fVoertuigen->size()-1; j > 0; j--){
            if(fVoertuigen->at(j)->isDeleteObject()){
                delete fVoertuigen->at(j);
            }
        }
        delete fVoertuigen;
        fVoertuigen = tempVoertuigen;
    }
}


void System::simpeleUitvoer(std::string& output) const {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling simpeleUitvoer");

    for(unsigned int i = 0; i<fBanen->size(); i++){
        output += ("\nBaan: " + fBanen->at(i)->getNaam() + "\n");
        output += ("\t-> snelheidslimiet: " + ToString(fBanen->at(i)->getSnelheidsLimiet()) + " km/h" + "\n");
        output += ("\t-> lengte: " + ToString(fBanen->at(i)->getLengte()) + " m" + "\n");
    }
    for(unsigned int i = 0; i<fWegenNetwerk->size(); i++){
        output += ("\nBaan: " + fWegenNetwerk->at(i)->getNaam() + "\n");
        output += ("\t-> snelheidslimiet: " + ToString(fWegenNetwerk->at(i)->getSnelheidsLimiet()) + " km/h" + "\n");
        output += ("\t-> lengte: " + ToString(fWegenNetwerk->at(i)->getLengte()) + " m" + "\n");
        output += ("\t-> verbinding: " + fWegenNetwerk->at(i)->getVerbinding() + "\n\n");
    }
    for(unsigned int i = 0; i<fVoertuigen->size(); i++){
        output += ("\nVoertuig: " + fVoertuigen->at(i)->getType() + " (" + fVoertuigen->at(i)->getNummerPlaat() + ")" + "\n");
        output += ("\t-> baan: " + fVoertuigen->at(i)->getBaan() + "\n");
        output += ("\t-> positie: " + ToString(fVoertuigen->at(i)->getPositie()) + " m" + "\n");
        output += ("\t-> snelheid: " + ToString(fVoertuigen->at(i)->getSnelheid()) + " km/h" + "\n");
    }

}

void System::simulate(unsigned int iterations) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling simulate");
    REQUIRE(iterations >= 0, "Iterations must be a positive integer");

    organizeVehicles();
    initializeVehicleBaanObject();
    initializeBaanVerbindingObjects();
    for(unsigned int i = 0; i < iterations; i++){
        for(unsigned int j = 0; j < fVoertuigen->size(); j ++){
            fVoertuigen->at(j)->updatePosition();
        }
        //remove to be deleted vehicles
        filterVehicles();
    }
}


void System::automaticSimulation(std::string& output) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling automaticSimulation");
    for(unsigned int i = 0; i < fBanen->size(); i++){
        fBanen->at(i)->sortVerkeersteken();
        fBanen->at(i)->assignZoneLimit();
    }
    while(fVoertuigen->size()>0){
        simulate();

        output += "+-----------------------------------------------------+\n";
        simpeleUitvoer(output);
    }
}

bool System::properlyInitialized() const{
    return _initCheck == this;
}

bool System::compareFiles(const std::string &p1, const std::string &p2) {
    // File compare
    // Source: https://stackoverflow.com/a/37575457/8076979
    std::ifstream f1(p1.c_str(), std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2.c_str(), std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail()) {
        return false; //file problem
    }

    if (f1.tellg() != f2.tellg()) {
        return false; //size mismatch
    }

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}
