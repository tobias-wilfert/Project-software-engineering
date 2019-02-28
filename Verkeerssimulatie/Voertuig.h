//
// Created by yanok on 28/02/2019.
//

#ifndef VERKEERSSIMULATIE_VOERTUIG_H
#define VERKEERSSIMULATIE_VOERTUIG_H

#include <string>

class Voertuig {
private:
    int positie;
    int snelheid;
    std::string baan;
    std::string type;
    std::string nummerPlaat;
public:
    Voertuig(const std::string &type, const std::string &nummerPlaat, const std::string &baan, int positie,
             unsigned int snelheid);

    const std::string &getType() const;

    Voertuig();

    void setType(const std::string &type);

    const std::string &getNummerPlaat() const;

    void setNummerPlaat(const std::string &nummerPlaat);

    const std::string &getBaan() const;

    void setBaan(const std::string &baan);

    int getPositie() const;

    void setPositie(int positie);

    int getSnelheid() const;

    void setSnelheid(int snelheid);

};


#endif //VERKEERSSIMULATIE_VOERTUIG_H
