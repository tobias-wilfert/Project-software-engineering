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
        std::cout << "\t-> baan: " << Voertuigen->at(i)->getBaan() << std::endl;
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

