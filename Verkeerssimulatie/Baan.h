//
// Created by yanok on 28/02/2019.
//

#ifndef VERKEERSSIMULATIE_BAAN_H
#define VERKEERSSIMULATIE_BAAN_H

#include <string>
#include "NullPointer.h"


class Baan {
private:
    double lengte;
    double snelheidsLimiet;
    std::string naam;
    std::string verbinding;
    Baan* verbindingObject;
public:
    Baan();

    virtual ~Baan();

    const std::string &getNaam() const;

    const std::string &getVerbinding() const;

    void setVerbinding(const std::string &verbinding);

    void setNaam(const std::string &naam);

    double getLengte() const;

    void setLengte(int lengte);

    double getSnelheidsLimiet() const;

    void setSnelheidsLimiet(int snelheidsLimiet);

    Baan *getVerbindingObject() const;

    void setVerbindingObject(Baan *verbinding);
};


#endif //VERKEERSSIMULATIE_BAAN_H
