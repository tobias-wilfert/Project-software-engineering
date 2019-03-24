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

    /// Pointer to a vector of pointers to all Instances of Banen in the System
    std::vector<Baan*>* fBanen;

    /// Pointer to a vector of pointers to all Instances of Wegen Netwerken in the System
    std::vector<Baan*>* fWegenNetwerk;

    /// Pointer to a vector of pointers to all Instances of Voertuigen in the System
    std::vector<Voertuig*>* fVoertuigen;

    /**
     * This method iterates over all Vehicles in the system letting everyone know
     * which the vehicle in front of them is.
     * @pre Voertuigen with NextVoertuig equal to 0
     * @post Voertuigen with fNextVoertuig a pointer to the Voertuig infront of them
     */
    void organizeVehicles();

    /**
     * This method iterates over all Vehicles in the system letting everyone know
     * which instance of Baan they are currently on.
     * @pre Voertuigen that only know the name of the Baan they are on
     * @post Voertuigen that have a pointer to the Baan they are on
     */
    void initializeVehicleBaanObject();

    /**
     *  This method iterates over all Wegen Netwerken in the system letting everyone
     *  know which instance of Baan they have a Verbinding with
     *  @pre Wegen Netwerken that only know the name of the Baan they have a verbinding with
     *  @post Wegen Netwerken that have a pointer to the Baan they have a verbinding with
     */
    void initializeBaanVerbindingObjects();

    /**
     *  Delete all vehicles from the system that isDeleteObject() true
     *  @pre Vehicles with isDeleteObject() true and Vehicles with isDeleteObject() false
     *  @post Vehicles with isDeleteObject() false
     */
    void filterVehicles();

public:

    System(std::vector<Baan *> *Banen, std::vector<Baan *> *WegenNetwerk, std::vector<Voertuig *> *Voertuigen);

    std::vector<Baan *> *getBanen() const;

    void setBanen(std::vector<Baan *> *Banen);

    std::vector<Baan *> *getWegenNetwerk() const;

    void setWegenNetwerk(std::vector<Baan *> *WegenNetwerk);

    std::vector<Voertuig *> *getVoertuigen() const;

    void setVoertuigen(std::vector<Voertuig *> *Voertuigen);

    /**
     * This outputs a Simple Texted Based Representation of how the System looks
     * @pre A Valid system
     * @post A Texted Based Representation of the System is printed to the Terminal
     */
    void simpeleUitvoer() const;

    /**
     * This method Simulates #iterations amount of time intervals in the system,
     * adjusting position, speed and acceleration of all vehicles based the optimal traffic flow formula
     * @pre A Valid system
     * @post Vehicles have adjusted speed, position and acceleration
     * @param iterations as Default 1, Specifies the number of iterations the system should simulate
     */
    void simulate(unsigned int iterations = 1);

    /**
     * This method calls simulate() till all Vehicles in the system are gone.
     * After each call of simulate() it also calls simpeleUitvoer() to show the current state of the system
     * @pre A Valid system
     * @post A system with no Vehicles in it
     */
    void automaticSimulation();
};


#endif //VERKEERSSIMULATIE_SYSTEM_H
