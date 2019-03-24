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

public:

    Baan();

    virtual ~Baan();

    const double &getLengte() const;

    void setLengte(const double &lengte);

    const std::string &getNaam() const;

    void setNaam(const std::string &naam);

    const int &getSnelheidsLimiet() const;

    void setSnelheidsLimiet(const int &snelheidsLimiet);

    const std::string &getVerbinding() const;

    void setVerbinding(const std::string &verbinding);

    Baan *getVerbindingObject() const;

    void setVerbindingObject(Baan *verbinding);
};


#endif //VERKEERSSIMULATIE_BAAN_H
