//
// Created by yanok on 28/02/2019.
//

#ifndef VERKEERSSIMULATIE_BAAN_H
#define VERKEERSSIMULATIE_BAAN_H

#include <string>

class Baan {
private:
    int lengte;
    int snelheidsLimiet;
    std::string naam;
    std::string verbinding;
public:
    Baan();

    const std::string &getNaam() const;

    void setNaam(const std::string &naam);

    int getLengte() const;

    void setLengte(int lengte);

    int getSnelheidsLimiet() const;

    void setSnelheidsLimiet(int snelheidsLimiet);

    const std::string &getVerbinding() const;

    void setVerbinding(const std::string &verbinding);
};


#endif //VERKEERSSIMULATIE_BAAN_H
