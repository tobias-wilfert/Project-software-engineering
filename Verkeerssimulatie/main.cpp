//============================================================================
// Name        : main.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 2.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "System.h"
#include "XmlParser.h"
#include "Verkeersteken.h"

// File compare
// Source: https://stackoverflow.com/a/37575457/8076979

#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

bool compareFiles(const std::string& p1, const std::string& p2) {
    std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail()) {
        return false; //file problem
    }

    if (f1.tellg() != f2.tellg()) {
        return false; //size mismatch
    }

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}

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
