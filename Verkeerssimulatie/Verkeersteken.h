//
// Created by reed on 27.04.19.
//

#ifndef VERKEERSSIMULATIE_VERKEERSTEKEN_H
#define VERKEERSSIMULATIE_VERKEERSTEKEN_H


#include <string>

class Verkeersteken {
protected:
    std::string fType;
    unsigned int fPositie;
    std::string fBaan;
    int fSnelheidslimiet; //initialized to 20000
    unsigned int fEndPositie;
public:
    unsigned int getFEndPositie() const;

    void setFEndPositie(unsigned int fEndPositie);

public:
    Verkeersteken():fSnelheidslimiet(20000){}
    int getFSnelheidslimiet() const;

    void setFSnelheidslimiet(int fSnelheidslimiet);

    const std::string &getFBaan() const;

    void setFBaan(const std::string &fBaan);

    unsigned int getFPositie() const;

    void setFPositie(unsigned int fPositie);

    void setFType(const std::string &fType);

    const std::string &getFType() const;

};


#endif //VERKEERSSIMULATIE_VERKEERSTEKEN_H
