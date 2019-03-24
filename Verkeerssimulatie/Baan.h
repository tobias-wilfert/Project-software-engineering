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

class Baan {
private:

    double fLengte;

    double fSnelheidsLimiet;

    std::string fNaam;

    std::string fVerbinding;

    Baan* fVerbindingObject;

public:
    Baan();

    virtual ~Baan();

    const double &getLengte() const;

    void setLengte(const double &lengte);

    const std::string &getNaam() const;

    void setNaam(const std::string &naam);

    const double &getSnelheidsLimiet() const;

    void setSnelheidsLimiet(const int &snelheidsLimiet);

    const std::string &getVerbinding() const;

    void setVerbinding(const std::string &verbinding);

    Baan *getVerbindingObject() const;

    void setVerbindingObject(Baan *verbinding);
};


#endif //VERKEERSSIMULATIE_BAAN_H
