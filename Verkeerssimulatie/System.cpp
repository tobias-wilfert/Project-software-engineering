//
// Created by Tobias Wilfert on 2019-03-06.
//

#include "System.h"

void System::setBanen(const std::vector<Baan> &Banen) {
    System::Banen = Banen;
}

void System::setVoertuigen(const std::vector<Voertuig> &Voertuigen) {
    System::Voertuigen = Voertuigen;
}

void System::simpeleUitvoer() const {
    for(int i = 0; i<Banen.size(); i++){
        std::cout << "Baan: " << Banen[i].getNaam() << std::endl;
        std::cout << "\tsnelheidslimiet: " << Banen[i].getSnelheidsLimiet() << " km/h" << std::endl;
        std::cout << "\tlengte: " << Banen[i].getLengte() << " m" << std::endl;
    }
    for(int i = 0; i<WegenNetwerk.size(); i++){
        std::cout << "Baan: " << Banen[i].getNaam() << std::endl;
        std::cout << "\tsnelheidslimiet: " << Banen[i].getSnelheidsLimiet() << " km/h" << std::endl;
        std::cout << "\tlengte: " << Banen[i].getLengte() << " m" << std::endl;
        std::cout << "\tverbinding: " << Banen[i].getVerbinding() << std::endl;
    }
    for(int i = 0; i<Voertuigen.size(); i++){
        std::cout << "Voertuig: " << Voertuigen[i].getType() << "(" << Voertuigen[i].getNummerPlaat() << ")"<< std::endl;
        std::cout << "\tbaan: " << Voertuigen[i].getBaan() << std::endl;
        std::cout << "\tpositie: " << Voertuigen[i].getPositie() << " m" << std::endl;
        std::cout << "\tsnelheid: " << Voertuigen[i].getSnelheid() << " km/h" << std::endl;
    }




}

void System::setWegenNetwerk(const std::vector<Baan> &WegenNetwerk) {
    System::WegenNetwerk = WegenNetwerk;
}
