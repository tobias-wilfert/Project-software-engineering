//
// Created by yanok on 28/02/2019.
//

#ifndef VERKEERSSIMULATIE_VOERTUIG_H
#define VERKEERSSIMULATIE_VOERTUIG_H

#include <string>
#include "NullPointer.h"

class Voertuig {
private:
    double positie;
    double snelheid;
    std::string baan;
    std::string type;
    std::string nummerPlaat;
    Voertuig* nextVoertuig;
public:
    Voertuig(const std::string &type, const std::string &nummerPlaat, const std::string &baan, double positie,
             double snelheid);
    Voertuig();

    void setNextVoertuig(Voertuig *nextVoertuig);
    void setPreviousVoertuig(Voertuig *previousVoertuig);


    const std::string &getType() const;


    void setType(const std::string &type);

    const std::string &getNummerPlaat() const;

    void setNummerPlaat(const std::string &nummerPlaat);

    const std::string &getBaan() const;

    void setBaan(const std::string &baan);

    double getPositie() const;

    void setPositie(int positie);

    double getSnelheid() const;

    void setSnelheid(int snelheid);


    void updatePosition();

};


#endif //VERKEERSSIMULATIE_VOERTUIG_H
