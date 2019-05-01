//============================================================================
// Name        : Verkeersteken.h
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#ifndef VERKEERSSIMULATIE_VERKEERSTEKEN_H
#define VERKEERSSIMULATIE_VERKEERSTEKEN_H

#include <string>

#include "DesignByContract.h"

class Verkeersteken {
private:

    /// Name of the Baan the Verkeersteken is on
    std::string fBaan;

    /// The type of the Verkeersteken
    std::string fType;

    /// The position of the Verkeersteken
    unsigned int fPositie;

    /// The end of the Verkeersteken (only applies to Zones)
    unsigned int fEndPositie;

    /// The speed limit of the Verkeersteken
    int fSnelheidslimiet; //initialized to 20000

    ///Use pointer to myself to verify whether I am properly initialized
    Verkeersteken * _initCheck;

public:

    /**
    \n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
     */
    Verkeersteken();

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFBaan");
     */
    const std::string &getFBaan() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFBaan");
    \n ENSURE(getFBaan() == baa, "setFType pre condition failure");
     */
    void setFBaan(const std::string &fBaan);

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFBaan");
     */
    const std::string &getFType() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFType");
    \n ENSURE(type == "BUSHALTE" or type == "ZONE" or type == "VERKEERSLICHT","setFType post condition failure" );
    \n ENSURE(getFType() == type, "setFType pre condition failure");
     */
    void setFType(const std::string &fType);

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFPositie");
     */
    unsigned int getFPositie() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFPositie");
    \n ENSURE( positie >= 0, "setFPositie post condition failure");
    \n ENSURE(getFPositie() == positie, "setFPositie pre condition failure");
     */
    void setFPositie(unsigned int fPositie);

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFSnelheidslimiet");
     */
    int getFSnelheidslimiet() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFSnelheidslimiet");
    \n ENSURE( fSnelheidslimiet >= 0, "setFSnelheidslimiet post condition failure");
    \n ENSURE(getFSnelheidslimiet() == fSnelheidslimiet, "setFSnelheidslimiet post condition failure");
     */
    void setFSnelheidslimiet(int fSnelheidslimiet);

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFEndPositie");
     */
    unsigned int getFEndPositie() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFEndPositie");
    \n ENSURE(fEndPositie >= 0,"setFEndPositie post condition failure" );
    \n ENSURE(getFEndPositie() == fEndPositie,"setFSnelheidslimiet post condition failure");
     */
    void setFEndPositie(unsigned int fEndPositie);

    //-----------------------------------------
    ///auxiliary routines (private use)
    //-----------------------------------------

    bool properlyInitialized() const;

};


#endif //VERKEERSSIMULATIE_VERKEERSTEKEN_H
