//
// Created by Tobias Wilfert on 2019-03-06.
//

#ifndef VERKEERSSIMULATIE_SYSTEM_H
#define VERKEERSSIMULATIE_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>

#include "Baan.h"
#include "Voertuig.h"

class System {
private:
    std::vector<Baan> Banen;
    std::vector<Baan> WegenNetwerk;
    std::vector<Voertuig> Voertuigen;
public:
    void setBanen(const std::vector<Baan> &Banen);

    void setWegenNetwerk(const std::vector<Baan> &WegenNetwerk);

    void setVoertuigen(const std::vector<Voertuig> &Voertuigen);

    void simpeleUitvoer() const;

};


#endif //VERKEERSSIMULATIE_SYSTEM_H
