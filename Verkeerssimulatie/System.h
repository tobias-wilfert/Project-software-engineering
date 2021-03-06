//============================================================================
// Name        : System.h
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#ifndef VERKEERSSIMULATIE_SYSTEM_H
#define VERKEERSSIMULATIE_SYSTEM_H

#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "Baan.h"
#include "Voertuig.h"

class System {
private:

    // Make friends for tests
    friend class BaanTest;
    friend class SystemTest;

    /// Pointer to a vector of pointers to all Instances of Banen in the System
    std::vector<Baan*>* fBanen;

    /// Pointer to a vector of pointers to all Instances of Wegen Netwerken in the System
    std::vector<Baan*>* fWegenNetwerk;

    /// Pointer to a vector of pointers to all Instances of Voertuigen in the System
    std::vector<Voertuig*>* fVoertuigen;

    /// Use pointer to myself to verify whether I am properly initialized
    System * _initCheck;

    /// Keeps track of the time passed since system started
    int counter;

public:

    /// Constructor

    /**
    \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     */
    System(std::vector<Baan *> *Banen, std::vector<Baan *> *WegenNetwerk, std::vector<Voertuig *> *Voertuigen);

    /// Getters and Setters

    /**
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling getBanen");
     */
    std::vector<Baan *> *getBanen() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling setBanen");
    \n ENSURE(getBanen() == fBanen, "setBanen post condition failure");
     */
    void setBanen(std::vector<Baan *> *Banen);

    /**
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling getWegenNetwerk");
     */
    std::vector<Baan *> *getWegenNetwerk() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling setWegenNetwerk");
    \n ENSURE(getWegenNetwerk() == fWegenNetwerk, "setWegenNetwerk post condition failure");
     */
    void setWegenNetwerk(std::vector<Baan *> *WegenNetwerk);

    /**
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling getVoertuigen");
     */
    std::vector<Voertuig *> *getVoertuigen() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling setVoertuigen");
    \n ENSURE(getVoertuigen() == fVoertuigen, "setVoertuigen post condition failure");
     */
    void setVoertuigen(std::vector<Voertuig *> *Voertuigen);

    /// Methods

    /**
     * Outputs a Simple Texted Based Representation of how the System looks
     * @pre A Valid system
     * @post A Texted Based Representation of the System is printed to the Terminal
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling simpeleUitvoer");
     */
    void simpeleUitvoer() const;

    /**
     * Simulates #iterations amount of time intervals in the system,
     * adjusting position, speed and acceleration of all vehicles based the optimal traffic flow formula
     * @pre A Valid system
     * @post Vehicles have adjusted speed, position and acceleration
     * @param iterations as Default 1, Specifies the number of iterations the system should simulate
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling simulate");
    \n REQUIRE(iterations >= 0, "Iterations must be a positive integer");
     */
    void simulate(unsigned int iterations = 1);

    /**
     * Calls simulate() till all Vehicles in the system are gone.
     * @pre A Valid system
     * @post A system with no Vehicles in it
     * @param type Specifieces which type of output should be used "simple" or "graphical"(ASSCI Art). Default simpele
     * @param fileName The name of a file the graphical impression should be writen to. Default grafischeOutput.txt
     * @param factor The scale that should be used to adjust the graphical representation. Default 1
     * @param time If 0 then every time interval is outputted else only the one of the given time. Default 0
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling automaticSimulation");
    \n REQUIRE(time >= 0, "When calling automaticSimulation() the parameter time must be a non negative number");
    \n REQUIRE(factor <= getLengthOfShortestBaan()/2, "When calling automaticSimulation() the factor must be smaller or equal than half of the shortest baan length");
    \n REQUIRE(fileName != "", "automaticSimulation() pre condition failure. Invalid fileName");
     */
    void automaticSimulation(std::string type = "simpele", std::string fileName="grafischeOutput",int factor = 1, int time = 0);

    /**
     * Outputs a graphical representation to a txt file
     * @param name The name of the file to write the output to
     * @param factor The scale that should be used to adjust the graphical representation
     * @param time If 0 then every time interval is outputted else only the one of the given time
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling grafischeImpressie");
    \n REQUIRE(time >= 0, "When calling grafischeImpressie() the parameter time must be a non negative number");
    \n REQUIRE(factor <= getLengthOfShortestBaan()/2, "When calling grafischeImpressie() the factor must be bigger or equal than half of the shortest baan length");
    \n REQUIRE(name != "", "grafischeImpressie() pre condition failure. Invalid name");
     */
    void grafischeImpressie(std::string name, int factor, int time);

    /// Helper Methods

    /**
     *  Iterates over all Wegen Netwerken in the system letting everyone
     *  know which instance of Baan they have a Verbinding with
     *  @pre Wegen Netwerken that only know the name of the Baan they have a verbinding with
     *  @post Wegen Netwerken that have a pointer to the Baan they have a verbinding with
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling initializeBaanVerbindingObjects");
    \n ENSURE(ensure,"initializeBaanVerbindingObjects() post condition failure");
     */
    void initializeBaanVerbindingObjects();

    /**
     * Iterates over all Vehicles in the system letting everyone know
     * which the vehicle in front of them is.
     * @pre Voertuigen with NextVoertuig equal to 0
     * @post Voertuigen with fNextVoertuig a pointer to the Voertuig infront of them
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling organizeVehicles");
    \n ENSURE(fVoertuigen->at(i)->getNextVoertuig()->getPositie() > fVoertuigen->at(i)->getPositie(),
                    "organizeVehicles post condition failure");
     */
    void organizeVehicles();

    /**
     * Iterates over all Vehicles in the system letting everyone know
     * which instance of Baan they are currently on.
     * @pre Voertuigen that only know the name of the Baan they are on
     * @post Voertuigen that have a pointer to the Baan they are on
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling initializeVehicleBaanObject");
    \n ENSURE(fVoertuigen->at(i)->getBaanObject()->getNaam() == fVoertuigen->at(i)->getBaan(),
                   "initializeVehicleBaanObject post condition failure");
     */
    void initializeVehicleBaanObject();

    /**
     *  Delete all vehicles from the system that isDeleteObject() true
     *  @pre Vehicles with isDeleteObject() true and Vehicles with isDeleteObject() false
     *  @post Vehicles with isDeleteObject() false
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling filterVehicles");
    \n ENSURE(fVoertuigen->at(i)->isDeleteObject() == false,"filterVehicles post condition failure");
     */
    void filterVehicles();

    /**
     * Returns a graphical representation of a baan
     * @param baan Pointer to the baan that should be represented
     * @param factor The scale that should be used to adjust the graphical representation
     * @return A string containing graphical representation of baan
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling outputBaan");
    \n REQUIRE(factor <= baan->getLengte()/2, "When calling outputBaan() the factor must be smaller or equal than half of baan length");

     */
    std::string outputBaan(Baan* baan, int factor);

    /**
     * Returns a graphical representation of the Verkeersteken on baan
     * @param baan Pointer to the baan that should be represented
     * @param factor he scale that should be used to adjust the graphical representation
     * @return A pair consisting  of a graphical representation of all Bushaltes and all Zones
    \n REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling outputVerkeersteken");
    \n REQUIRE(factor <= baan->getLengte()/2, "When calling outputVerkeersteken() the factor must be bigger or equal than half of baan length");
     */
    std::pair<std::string,std::string> outputVerkeersteken(Baan* baan, int factor);

    //-----------------------------------------
    ///auxiliary routines (private use)
    //-----------------------------------------

    bool properlyInitialized() const;

    int getLengthOfShortestBaan() const;

    /**
     * Checks whether the contents of two files ar the same
     * @param p1 Location and name of the first file
     * @param p2 Location and name of the second file
     * @return True if the content of p1 and p2 are the same
    \n REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling compareFiles");
     */
    bool compareFiles(const std::string& p1, const std::string& p2);

};


#endif //VERKEERSSIMULATIE_SYSTEM_H
