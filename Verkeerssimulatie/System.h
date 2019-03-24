//============================================================================
// Name        : System.h
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#ifndef VERKEERSSIMULATIE_SYSTEM_H
#define VERKEERSSIMULATIE_SYSTEM_H

#include <vector>
#include <iostream>
#include "Baan.h"
#include "Voertuig.h"

class System {
private:
    std::vector<Baan*>* Banen;
    std::vector<Baan*>* WegenNetwerk;
    std::vector<Voertuig*>* Voertuigen;

public:

    System(std::vector<Baan *> *Banen, std::vector<Baan *> *WegenNetwerk, std::vector<Voertuig *> *Voertuigen);

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
