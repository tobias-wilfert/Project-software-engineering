//============================================================================
// Name        : Voertuig.h
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#ifndef VERKEERSSIMULATIE_VOERTUIG_H
#define VERKEERSSIMULATIE_VOERTUIG_H

#include "Baan.h"
#include "DesignByContract.h"

class Voertuig {
private:

    /// The length of the Vehicle (3m per default)
    double fLengte;

    /// The position of the Vehicle on a Baan in m from the start
    double fPositie;

    /// Speed of the Vehicle in km/h
    double fSnelheid;

    /// Ths old Position of the Vehicle before the last time interval
    double fOldPositie;

    /// The acceleration of the vehicle
    double fVersnelling;

    /// The name of the Baan the Vehicle is on
    std::string fBaan;

    /// The Type of the Vehicle
    std::string fType;

    /// The number Plate of the Vehicle used as unique ID
    std::string fNummerPlaat;

    /// A pointer to the Baan the Vehicle is currently on
    Baan* fBaanObject;

    /// A pointer to the Vehicle in front of this Vehicle
    Voertuig* fNextVoertuig;

    /// Boolean value that is true if the vehicle should be deleted
    bool fDeleteObject;

    ///Use pointer to myself to verify whether I am properly initialized
    Voertuig * _initCheck;

    ///maximum speed the vehicle can achieve
    double fMaxSnelheid;

    ///maximum accelerationthe vehicle can achieve
    double fMaxVersnelling;

public:
    double getFVersnelling() const;

    void setFVersnelling(double fVersnelling);

public:
    double getFMaxSnelheid() const;

    void setFMaxSnelheid(double fMaxSnelheid);

    double getFMaxVersnelling() const;

    void setFMaxVersnelling(double fMaxVersnelling);

    double getFMinVersnelling() const;

    void setFMinVersnelling(double fMinVersnelling);

private:
///minimum acceleration the vehicle can achieve
    double fMinVersnelling;

public:

    /**
    \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     */
    Voertuig();

    virtual ~Voertuig();

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getLengte");
     */
    double getLengte() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setLengte");
    \n REQUIRE(lengte > 0, "Lengte must be a positive double");
    \n ENSURE(getLengte() == fLengte, "setLengte post condition failure");
     */
    void setLengte(double lengte);

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getPositie");
     */
    double getPositie() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setPositie");
    \n REQUIRE(positie >= 0, "Positie must be a positive integer");
    \n ENSURE(getPositie() == fPositie, "setPositie post condition failure");
     */
    void setPositie(int positie);

    /**
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getSnelheid");
     */
    double getSnelheid() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setSnelheid");
    \n REQUIRE(snelheid >= 0, "Snelheid must be a positive integer");
    \n ENSURE(getSnelheid() == fSnelheid, "setSnelheid post condition failure");
     */
    void setSnelheid(int snelheid);

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getOldPositie");
     */
    double getOldPositie() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setOldPositie");
    \n REQUIRE(oldPositie >= 0, "oldPositie must be a positive double");
    \n ENSURE(getOldPositie() == fOldPositie, "setOldPositie post condition failure");
     */
    void setOldPositie(double oldPositie);

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getBaan");
     */
    const std::string &getBaan() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setBaan");
    \n REQUIRE(baan != "", "Baan must be a non empty string");
    \n ENSURE(getBaan() == fBaan, "setBaan post condition failure");
     */
    void setBaan(const std::string &baan);

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getType");
     */
    const std::string &getType() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setType");
    \n REQUIRE(type != "", "Type must be a non empty string");
    \n ENSURE(getType() == fType, "setType post condition failure");
     */
    void setType(const std::string &type);

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getNummerPlaat");
     */
    const std::string &getNummerPlaat() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setNummerPlaat");
    \n REQUIRE(nummerPlaat != "", "NummerPlaat must be a non empty string");
    \n ENSURE(getNummerPlaat() == fNummerPlaat, "setNummerPlaat post condition failure");
     */
    void setNummerPlaat(const std::string &nummerPlaat);

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getBaanObject");
     */
    Baan *getBaanObject() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setBaanObject");
    \n ENSURE(getBaanObject() == fBaanObject, "setBaanObject post condition failure");
     */
    void setBaanObject(Baan *baanObject);

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getFNextVoertuig");
     */
    Voertuig *getNextVoertuig() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setNextVoertuig");
    \n ENSURE(getFNextVoertuig() == fNextVoertuig, "setNextVoertuig post condition failure");
     */
    void setNextVoertuig(Voertuig *nextVoertuig);

    /**
    \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling isDeleteObject");
     */
    bool isDeleteObject() const;

    /**
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setDeleteObject");
    ENSURE(isDeleteObject() == fDeleteObject, "setDeleteObject post condition failure");
     */
    void setDeleteObject(bool deleteObject);

    /**
     * This method updates the position of the the Vehicle as well as speed and acceleration
     * @pre A valid Vehicle
     * @post A Vehicle with updated position, speed and acceleration
     \n REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling updatePosition");
     \n ENSURE(fPositie <= fBaanObject->getLengte(), "updatePosition post condition failure");
     \n ENSURE(fSnelheid <= fBaanObject->getSnelheidsLimiet(), "updatePosition post condition failure");
     \n ENSURE(versnelling <= 2, "updatePosition post condition failure");
     \n ENSURE(versnelling >= -8, "updatePosition post condition failure");
     */
    void updatePosition();













    //-----------------------------------------
    ///auxiliary routines (private use)
    //-----------------------------------------

    bool properlyInitialized() const;

    void set_initCheck(Voertuig *_initCheck);

};


#endif //VERKEERSSIMULATIE_VOERTUIG_H
