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

public:

    Voertuig();

    virtual ~Voertuig();

    double getLengte() const;

    void setLengte(double lengte);

    double getPositie() const;

    void setPositie(int positie);

    double getSnelheid() const;

    void setSnelheid(int snelheid);

    double getOldPositie() const;

    void setOldPositie(double oldPositie);

    const std::string &getBaan() const;

    void setBaan(const std::string &baan);

    const std::string &getType() const;

    void setType(const std::string &type);

    const std::string &getNummerPlaat() const;

    void setNummerPlaat(const std::string &nummerPlaat);

    Baan *getBaanObject() const;

    void setBaanObject(Baan *baanObject);

    Voertuig *getFNextVoertuig() const;

    void setNextVoertuig(Voertuig *nextVoertuig);

    bool isDeleteObject() const;

    void setDeleteObject(bool deleteObject);

    /**
     * This method updates the position of the the Vehicle as well as speed and acceleration
     * @pre A valid Vehicle
     * @post A Vehicle with updated position, speed and acceleration
     */
    void updatePosition();

};


#endif //VERKEERSSIMULATIE_VOERTUIG_H
