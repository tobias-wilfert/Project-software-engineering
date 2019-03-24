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

    double fLengte;

    double fPositie;

    double fSnelheid;

    double fOldPositie;

    std::string fBaan;

    std::string fType;

    std::string fNummerPlaat;

    Baan* fBaanObject;

    Voertuig* fNextVoertuig;

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

    // Method's (that aren't getters or setters)

    void updatePosition();

};


#endif //VERKEERSSIMULATIE_VOERTUIG_H
