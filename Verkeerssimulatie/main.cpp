#include <iostream>
#include "System.h"
#include "XmlParser.h"

int main() {

    const char* fileName =  "Wegen_en_voertuigen.xml";

    XmlParser parser = XmlParser(fileName);

    System system = System();
    system.setBanen(parser.getBanen());
    system.setWegenNetwerk(parser.getWegenNetwerk());
    system.setVoertuigen(parser.getVoertuigen());
    system.simpeleUitvoer();
    system.organizeVehicles();
    std::cout << "\n \n \n #######################################################################" << std::endl;

    //system.beginSimulation(500);
    //system.simpeleUitvoer();
    system.automaticSimulation();

    std::cout << "The program executed till here without crashing." << std::endl;
    return 0;
}
