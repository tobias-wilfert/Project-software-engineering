//============================================================================
// Name        : System.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "System.h"

System::System(std::vector<Baan *> *Banen, std::vector<Baan *> *WegenNetwerk, std::vector<Voertuig *> *Voertuigen)
        : fBanen(Banen), fWegenNetwerk(WegenNetwerk), fVoertuigen(Voertuigen) {}

std::vector<Baan *> *System::getBanen() const {
    return fBanen;
}

void System::setBanen(std::vector<Baan *> *Banen) {
    System::fBanen = Banen;
}

std::vector<Baan *> *System::getWegenNetwerk() const {
    return fWegenNetwerk;
}

void System::setWegenNetwerk(std::vector<Baan *> *WegenNetwerk) {
    System::fWegenNetwerk = WegenNetwerk;
}

std::vector<Voertuig *> *System::getVoertuigen() const {
    return fVoertuigen;
}

void System::setVoertuigen(std::vector<Voertuig *> *Voertuigen) {
    System::fVoertuigen = Voertuigen;
}

void System::organizeVehicles() {
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

void System::simpeleUitvoer() const {
    for(unsigned int i = 0; i<fBanen->size(); i++){
        std::cout << "\nBaan: " << fBanen->at(i)->getNaam() << std::endl;
        std::cout << "\t-> snelheidslimiet: " << fBanen->at(i)->getSnelheidsLimiet() << " km/h" << std::endl;
        std::cout << "\t-> lengte: " << fBanen->at(i)->getLengte() << " m" << std::endl;
    }
    for(unsigned int i = 0; i<fWegenNetwerk->size(); i++){
        std::cout << "\nBaan: " << fWegenNetwerk->at(i)->getNaam() << std::endl;
        std::cout << "\t-> snelheidslimiet: " << fWegenNetwerk->at(i)->getSnelheidsLimiet() << " km/h" << std::endl;
        std::cout << "\t-> lengte: " << fWegenNetwerk->at(i)->getLengte() << " m" << std::endl;
        std::cout << "\t-> verbinding: " << fWegenNetwerk->at(i)->getVerbinding() << std::endl << std::endl;
    }
    for(unsigned int i = 0; i<fVoertuigen->size(); i++){
        std::cout << "\nVoertuig: " << fVoertuigen->at(i)->getType() << " (" << fVoertuigen->at(i)->getNummerPlaat() << ")"<< std::endl;
        std::cout << "\t-> baan: " << fVoertuigen->at(i)->getBaan()<< std::endl;
        std::cout << "\t-> positie: " << fVoertuigen->at(i)->getPositie() << " m" << std::endl;
        std::cout << "\t-> snelheid: " << fVoertuigen->at(i)->getSnelheid() << " km/h" << std::endl;
    }

}

void System::simulate(unsigned int iterations) {
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

void System::automaticSimulation() {

    while(fVoertuigen->size()>0){
        simulate();
        std::cout << "\n " << std::endl;
        std::cout << "+-----------------------------------------------------+" << std::endl;
        simpeleUitvoer();
    }
}
