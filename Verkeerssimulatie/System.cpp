//
// Created by Tobias Wilfert on 2019-03-06.
//

#include "System.h"



std::vector<Baan *> *System::getBanen() const {
    return Banen;
}

std::vector<Baan *> *System::getWegenNetwerk() const {
    return WegenNetwerk;
}

std::vector<Voertuig *> *System::getVoertuigen() const {
    return Voertuigen;
}

void System::simpeleUitvoer() const {
    for(unsigned int i = 0; i<Banen->size(); i++){
        std::cout << "\nBaan: " << Banen->at(i)->getNaam() << std::endl;
        std::cout << "\t-> snelheidslimiet: " << Banen->at(i)->getSnelheidsLimiet() << " km/h" << std::endl;
        std::cout << "\t-> lengte: " << Banen->at(i)->getLengte() << " m" << std::endl;
    }
    for(unsigned int i = 0; i<WegenNetwerk->size(); i++){
        std::cout << "\nBaan: " << WegenNetwerk->at(i)->getNaam() << std::endl;
        std::cout << "\t-> snelheidslimiet: " << WegenNetwerk->at(i)->getSnelheidsLimiet() << " km/h" << std::endl;
        std::cout << "\t-> lengte: " << WegenNetwerk->at(i)->getLengte() << " m" << std::endl;
        std::cout << "\t-> verbinding: " << WegenNetwerk->at(i)->getVerbinding() << std::endl << std::endl;
    }
    for(unsigned int i = 0; i<Voertuigen->size(); i++){
        std::cout << "\nVoertuig: " << Voertuigen->at(i)->getType() << " (" << Voertuigen->at(i)->getNummerPlaat() << ")"<< std::endl;
        std::cout << "\t-> baan: " << Voertuigen->at(i)->getBaan()<< std::endl;
        std::cout << "\t-> positie: " << Voertuigen->at(i)->getPositie() << " m" << std::endl;
        std::cout << "\t-> snelheid: " << Voertuigen->at(i)->getSnelheid() << " km/h" << std::endl;
    }




}

void System::setBanen(std::vector<Baan *> *Banen) {
    System::Banen = Banen;
}

void System::setWegenNetwerk(std::vector<Baan *> *WegenNetwerk) {
    System::WegenNetwerk = WegenNetwerk;
}

void System::setVoertuigen(std::vector<Voertuig *> *Voertuigen) {
    System::Voertuigen = Voertuigen;
}

void System::simulate(unsigned int elapsedTime) {
    //nieuwe positie voertuig berekenen
    for(unsigned int i = 0; i<Voertuigen->size(); i++){
        //calculate
        //Voertuig* currentVoertuig = Voertuigen->at(i);
        //double tempPos = currentVoertuig->getSnelheid()*elapsedTime+currentVoertuig->getPositie() ;

    }
}

void System::organizeVehicles() {
    for(unsigned int i = 0; i<Voertuigen->size(); i++){
        Voertuig* tempNextVoertuig;
        bool isFirst = true;
        for(unsigned int j = 0; j<Voertuigen->size(); j++){
            if(j == i){
                continue;
            }
            else if(Voertuigen->at(j)->getBaan() == Voertuigen->at(i)->getBaan()){ //check of auto op dezelfde baan zit
                //check of dat de auto voor onze voertuig zit
                if(Voertuigen->at(j)->getPositie()-Voertuigen->at(i)->getPositie()>0){
                    if(isFirst){ //als wij een auto gevonden hebben en als de tempNextVoertuig nog geen waarde heeft
                        tempNextVoertuig = Voertuigen->at(j);
                        isFirst = false;
                    }
                    else if(tempNextVoertuig->getPositie()>Voertuigen->at(j)->getPositie()){
                        tempNextVoertuig = Voertuigen->at(j);
                    }
                }
            }
        }
        if(!isFirst){ //alleen setten als tempNextVoertuig bestaat
            Voertuigen->at(i)->setNextVoertuig(tempNextVoertuig);
        }
    }
}

void System::beginSimulation(int iterations) {
    organizeVehicles();
    initializeVehicleBaanObject();
    initializeBaanVerbindingObjects();
    for(int i = 0; i < iterations; i++){
        for(unsigned int j = 0; j < Voertuigen->size(); j ++){
            Voertuigen->at(j)->updatePosition();
        }
        //remove to be deleted vehicles
        filterVehicles();

    }
}

void System::initializeVehicleBaanObject() {
    for(unsigned int i = 0; i < Voertuigen->size(); i++){
        bool found = false;
        std::string currentVehicleWay = Voertuigen->at(i)->getBaan();
        for(unsigned int j = 0; j < Banen->size(); j++){
            if(currentVehicleWay == Banen->at(j)->getNaam()){
                Voertuigen->at(i)->setBaanObject(Banen->at(j));
                found = true;
            }
        }
        if(!found){
            for(unsigned int j = 0; j < WegenNetwerk->size(); j++){
                if(currentVehicleWay == WegenNetwerk->at(j)->getNaam()){
                    Voertuigen->at(i)->setBaanObject(WegenNetwerk->at(j));
                }
            }
        }
    }
}

void System::initializeBaanVerbindingObjects() {
    for(unsigned int i = 0; i < WegenNetwerk->size(); i++){
        bool found = false;
        std::string currentWay = WegenNetwerk->at(i)->getVerbinding();
        for(unsigned int j = 0; j < Banen->size(); j++){
            if(currentWay == Banen->at(j)->getNaam()){
                WegenNetwerk->at(i)->setVerbindingObject(Banen->at(j));
                found = true;
            }
        }
        if(!found){
            for(unsigned int j = 0; j < WegenNetwerk->size(); j++){
                if(currentWay == WegenNetwerk->at(j)->getNaam()){
                    WegenNetwerk->at(i)->setVerbindingObject(WegenNetwerk->at(j));
                }
            }

        }
    }

}

void System::filterVehicles() {
    std::vector<Voertuig*>* tempVoertuigen = new std::vector<Voertuig*>;
    if(Voertuigen->size() > 0){
        for(unsigned int i = 0; i < Voertuigen->size(); i++){
            if(!Voertuigen->at(i)->isDeleteObject()){//if vehicle is not to be deleted then place this to a vector
                tempVoertuigen->push_back(Voertuigen->at(i));
            }
        }
        for(unsigned long j = Voertuigen->size()-1; j > 0; j--){
            if(Voertuigen->at(j)->isDeleteObject()){
                delete Voertuigen->at(j);
            }
        }
        delete Voertuigen;
        Voertuigen = tempVoertuigen;
    }

}

void System::automaticSimulation() {
    while(Voertuigen->size()>0){
        beginSimulation();
        std::cout << "\n \n \n #######################################################################" << std::endl;
        simpeleUitvoer();
    }

}

