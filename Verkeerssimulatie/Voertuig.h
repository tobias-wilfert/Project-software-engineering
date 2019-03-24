//============================================================================
// Name        : Voertuig.h
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#ifndef VERKEERSSIMULATIE_VOERTUIG_H
#define VERKEERSSIMULATIE_VOERTUIG_H

#include <vector>
#include "Baan.h"

class Voertuig {
private:
    double lengte;
    double oldPositie;
    double positie;
    double snelheid;
    std::string baan;
    std::string type;
    std::string nummerPlaat;
    Voertuig* nextVoertuig;
    Baan* baanObject;
    bool deleteObject;


public:
    Baan *getBaanObject() const;

    void setBaanObject(Baan *baanObject);

    bool isDeleteObject() const;

    void setLengte(double lengte);

    void setDeleteObject(bool deleteObject);

    Voertuig(const std::string &type, const std::string &nummerPlaat, std::string baan, double positie,
             double snelheid);
    Voertuig();

    const std::string &getBaan() const;

    void setBaan(const std::string &baan);

    void setNextVoertuig(Voertuig *nextVoertuig);

    const std::string &getType() const;


    void setType(const std::string &type);

    const std::string &getNummerPlaat() const;

    void setNummerPlaat(const std::string &nummerPlaat);



    double getPositie() const;

    void setPositie(int positie);

    double getSnelheid() const;

    void setSnelheid(int snelheid);

    double getLengte() const;

    double getOldPositie() const;

    void setOldPositie(double oldPositie);

    void updatePosition();

    virtual ~Voertuig();

};


#endif //VERKEERSSIMULATIE_VOERTUIG_H
