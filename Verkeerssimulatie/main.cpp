//============================================================================
// Name        : main.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "System.h"
#include "XmlParser.h"
#include "Verkeersteken.h"

int main(int argc, char** argv) {

    // The name of the file that will serve as input
    //const char* kFileName =  "Traffic_Jam.xml";
    //const char* kFileName =  "Friday_Night.xml";
    //const char* kFileName =  "Holiday.xml";
    //const char* kFileName =  "Monday_Morning.xml";
    //const char* kFileName =  "Wednesday_Night.xml";
    //const char* kFileName =  "Wegen_en_voertuigen.xml";
    //const char* kFileName =  "Wegennetwerk.xml";
    //const char* kFileName = argv[1];

    std::string output;

    const char* kFileName = "verkeersTekenVB.xml";
    // Parse the file
    XmlParser parser = XmlParser(kFileName);
    // Initialize the system
    System system = System(parser.getBanen(),parser.getWegenNetwerk(),parser.getVoertuigen());
    // Start the simulation
    system.getBanen()->at(0)->getFVerkeerstekens().at(1)->getFSnelheidslimiet();
    system.automaticSimulation(output);
    std::cout << output;
    return 0;
}
