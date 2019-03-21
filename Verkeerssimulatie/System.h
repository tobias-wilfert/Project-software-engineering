//
// Created by Tobias Wilfert on 2019-03-06.
//

#ifndef VERKEERSSIMULATIE_SYSTEM_H
#define VERKEERSSIMULATIE_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "Baan.h"
#include "Voertuig.h"

class System {
private:
    std::vector<Baan*>* Banen;
    std::vector<Baan*>* WegenNetwerk;
    std::vector<Voertuig*>* Voertuigen;
    //std::map<std::string ,std::vector<Voertuig*>*> organizedVehicles;
public:
    std::vector<Baan *> *getBanen() const;

    std::vector<Baan *> *getWegenNetwerk() const;

    std::vector<Voertuig *> *getVoertuigen() const;

    void simpeleUitvoer() const;

    void setBanen(std::vector<Baan *> *Banen);

    void setWegenNetwerk(std::vector<Baan *> *WegenNetwerk);

    void setVoertuigen(std::vector<Voertuig *> *Voertuigen);

    void simulate(unsigned int elapsedTime = 1);

    void organizeVehicles();

    void initializeVehicleBaanObject();
    void beginSimulation(int iterations = 1);

    void initializeBaanVerbindingObjects();

    void filterVehicles(); //removes invalid vehicles (vehicles with position out of bounds)

    void automaticSimulation();
};


#endif //VERKEERSSIMULATIE_SYSTEM_H
