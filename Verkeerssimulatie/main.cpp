//============================================================================
// Name        : main.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "System.h"
#include "XmlParser.h"
#include "Verkeersteken.h"

int main(int argc, char** argv) {

    // The name of the file that will serve as input
    //const char* kFileName = argv[1];
    const char* kFileName =  "SystemOutput/BusTest.xml";

    // SOURCE: https://stackoverflow.com/a/50650024/8076979
    // Redirect streams
    // std::ofstream out("SystemOutput/BusTest.txt");
    // std::cout.rdbuf(out.rdbuf());

    // Parse the file
    XmlParser parser = XmlParser(kFileName);

    // Initialize the system
    System system = System(parser.getBanen(),parser.getWegenNetwerk(),parser.getVoertuigen());

    // Start the simulation
    system.automaticSimulation("simpele");
    //system.automaticSimulation("graphical","grafischeOutput",10);

    return 0;
}
