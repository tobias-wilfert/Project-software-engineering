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

    std::vector<Baan*>* fBanen;

    std::vector<Baan*>* fWegenNetwerk;

    std::vector<Voertuig*>* fVoertuigen;

public:

    System(std::vector<Baan *> *Banen, std::vector<Baan *> *WegenNetwerk, std::vector<Voertuig *> *Voertuigen);

    std::vector<Baan *> *getBanen() const;

    void setBanen(std::vector<Baan *> *Banen);

    std::vector<Baan *> *getWegenNetwerk() const;

    void setWegenNetwerk(std::vector<Baan *> *WegenNetwerk);

    std::vector<Voertuig *> *getVoertuigen() const;

    void setVoertuigen(std::vector<Voertuig *> *Voertuigen);

    // Method's that aren't getters and setters
    // TODO: Check which need to be public

    void organizeVehicles();

    void initializeVehicleBaanObject();

    void initializeBaanVerbindingObjects();

    void filterVehicles(); //removes invalid vehicles (vehicles with position out of bounds)

    void simpeleUitvoer() const;

    void simulate(unsigned int iterations = 1);

    void automaticSimulation();
};


#endif //VERKEERSSIMULATIE_SYSTEM_H
