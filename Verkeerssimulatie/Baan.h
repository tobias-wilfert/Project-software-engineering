//============================================================================
// Name        : Baan.h
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#ifndef VERKEERSSIMULATIE_BAAN_H
#define VERKEERSSIMULATIE_BAAN_H

#include <string>
#include "DesignByContract.h"
#include "Verkeersteken.h"
#include <vector>
class Baan {
private:

    /// Length of the Baan in meters
    double fLengte;

    /// The speed Limit of the Baan in km/h represented as an integer
    int fSnelheidsLimiet;

    /// The Name of the Baan represented as a string
    std::string fNaam;

    /// The Name of the Baan that this Baan has a Verbinding with
    std::string fVerbinding;

    /// A pointer to the instance of Baan that this Instance has a Verbining with
    Baan* fVerbindingObject;

    Baan * _initCheck;

    /// A collection of road regulations
    std::vector<Verkeersteken*> fVerkeerstekens;

    int fRijstroken;
public:
    int getFRijstroken() const;

    void setFRijstroken(int fRijstroken);


public:
    /**
    \n ENSURE(properlyInitialized(), "Constructor must end in properly initialized state");
    */
    Baan();

    virtual ~Baan();

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getLengte()");
    */
    const double &getLengte() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setLengte()");
    \n REQUIRE(lengte > 0, "setLengte precondition failure");
    \n ENSURE(fLengte > 0, "setLengte postcondition failure");
    */
    void setLengte(const double &lengte);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getNaam()");
    */
    const std::string &getNaam() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setNaam()");
    \n REQUIRE(!naam.empty(), "setNaam() precondition failure");
    \n ENSURE(getNaam() == fNaam, "setNaam() post condition failure");
    */
    void setNaam(const std::string &naam);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getSnelheidsLimiet()");
    */
    const int &getSnelheidsLimiet() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setSnelheidsLimiet()");
    \n REQUIRE(snelheidsLimiet > 0, "setSnelheidsLimiet() precondition failure");
    \n ENSURE(snelheidsLimiet == fSnelheidsLimiet, "setSnelheidsLimiet() postcondition failure");
    */
    void setSnelheidsLimiet(const int &snelheidsLimiet);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getVerbinding");
    */
    const std::string &getVerbinding() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setVerbinding");
    \n REQUIRE(fVerbinding != "", "setVerbinding() precondition failure");
    \n ENSURE(getVerbinding() == fVerbinding, "setVerbinding() postcondition failure");
    */
    void setVerbinding(const std::string &verbinding);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getVerbindingObject()");
    */
    Baan *getVerbindingObject() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setVerbindingObject()");
    \n REQUIRE(verbinding != NULL, "setVerbindingObject() precondition failure");
    \n ENSURE(fVerbindingObject = getVerbindingObject(), "setVerbindingObject() postcondition failure");
    */
    void setVerbindingObject(Baan *verbinding);

    //-----------------------------------------
    ///auxiliary routines (private use)
    //-----------------------------------------

    bool properlyInitialized() const;


    const std::vector<Verkeersteken *> &getFVerkeerstekens() const;


    void addFVerkeersteken(Verkeersteken* verkeersteken);

    void sortVerkeersteken();

    bool isSorted();

    void assignZoneLimit();
};


#endif //VERKEERSSIMULATIE_BAAN_H