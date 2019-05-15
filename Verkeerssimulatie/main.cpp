//============================================================================
// Name        : main.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 2.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <fstream>

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
    const char* kFileName = "BusTest.xml";
    //const char* kFileName =  "Wegennetwerk.xml";
    //const char* kFileName = argv[1];

    /// Print errors to file
    // SOURCE: https://stackoverflow.com/a/50650024/8076979
    // Determine file name
    // std::ofstream out("Parser/AllMurphy.txt");
    // std::cerr.rdbuf(out.rdbuf());

    // Parse the file
    XmlParser parser = XmlParser(kFileName);
    // Initialize the system
    System system = System(parser.getBanen(),parser.getWegenNetwerk(),parser.getVoertuigen());
    // Start the simulation
    system.automaticSimulation();

    return 0;
}
