//============================================================================
// Name        : main.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "System.h"
#include "XmlParser.h"

int main() {

    // The name of the file that will serve as input
    const char* kFileName =  "Traffic_Jam.xml";
    //const char* kFileName =  "Friday_Night.xml";
    //const char* kFileName =  "Holiday.xml";
    //const char* kFileName =  "Monday_Morning.xml";
    //const char* kFileName =  "Wednesday_Night.xml";
    //const char* kFileName =  "Wegen_en_voertuigen.xml";
    //const char* kFileName =  "Wegennetwerk.xml";

    // Parse the file
    XmlParser parser = XmlParser(kFileName);
    // Initialize the system
    System system = System(parser.getBanen(),parser.getWegenNetwerk(),parser.getVoertuigen());
    // Start the simulation
    system.automaticSimulation();

    return 0;
}
