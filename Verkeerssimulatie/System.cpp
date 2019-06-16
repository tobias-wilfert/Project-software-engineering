//============================================================================
// Name        : System.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "System.h"
#include <string>
#include <sstream>
#include <algorithm>

template <typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}



System::System(std::vector<Baan *> *Banen, std::vector<Baan *> *WegenNetwerk, std::vector<Voertuig *> *Voertuigen)
        : fBanen(Banen), fWegenNetwerk(WegenNetwerk), fVoertuigen(Voertuigen), counter(0) {
    _initCheck = this;

    for(unsigned int j = 0; j < fBanen->size(); j++){
        fBanen->at(j)->setfContainsBushalte();
    }
    for(unsigned int j = 0; j < fWegenNetwerk->size(); j++){
        fWegenNetwerk->at(j)->setfContainsBushalte();
    }

    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

std::vector<Baan *> *System::getBanen() const {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling getBanen");
    return fBanen;
}

void System::setBanen(std::vector<Baan *> *Banen) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling setBanen");
    System::fBanen = Banen;
    ENSURE(getBanen() == fBanen, "setBanen post condition failure");
}

std::vector<Baan *> *System::getWegenNetwerk() const {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling getWegenNetwerk");
    return fWegenNetwerk;
}

void System::setWegenNetwerk(std::vector<Baan *> *WegenNetwerk) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling setWegenNetwerk");
    System::fWegenNetwerk = WegenNetwerk;
    ENSURE(getWegenNetwerk() == fWegenNetwerk, "setWegenNetwerk post condition failure");
}

std::vector<Voertuig *> *System::getVoertuigen() const {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling getVoertuigen");
    return fVoertuigen;
}

void System::setVoertuigen(std::vector<Voertuig *> *Voertuigen) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling setVoertuigen");
    System::fVoertuigen = Voertuigen;
    ENSURE(getVoertuigen() == fVoertuigen, "setVoertuigen post condition failure");
}

void System::organizeVehicles() {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling organizeVehicles");

    for(unsigned int i = 0; i<fVoertuigen->size(); i++){
        Voertuig* tempNextVoertuig = NULL;
        bool isFirst = true;
        for(unsigned int j = 0; j<fVoertuigen->size(); j++){
            if(j == i){
                continue;
            }
            else if(fVoertuigen->at(j)->getBaan() == fVoertuigen->at(i)->getBaan()){ //check of auto op dezelfde baan zit
                //check of dat de auto voor onze voertuig zit
                if(fVoertuigen->at(j)->getPositie()-fVoertuigen->at(i)->getPositie()>0){
                    if(isFirst){ //als wij een auto gevonden hebben en als de tempNextVoertuig nog geen waarde heeft
                        tempNextVoertuig = fVoertuigen->at(j);
                        isFirst = false;
                    }
                    else if(tempNextVoertuig->getPositie()>fVoertuigen->at(j)->getPositie()){
                        tempNextVoertuig = fVoertuigen->at(j);
                    }
                }
            }
        }

        fVoertuigen->at(i)->setNextVoertuig(tempNextVoertuig);
    }

    for(unsigned int i = 0; i<fVoertuigen->size(); i++){
        if (fVoertuigen->at(i)->getNextVoertuig() != NULL){
            ENSURE(fVoertuigen->at(i)->getNextVoertuig()->getPositie() > fVoertuigen->at(i)->getPositie(),
                    "organizeVehicles post condition failure");
        }
    }
}

void System::initializeVehicleBaanObject() {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling initializeVehicleBaanObject");

    for(unsigned int i = 0; i < fVoertuigen->size(); i++){
        bool found = false;
        std::string currentVehicleWay = fVoertuigen->at(i)->getBaan();
        for(unsigned int j = 0; j < fBanen->size(); j++){
            if(currentVehicleWay == fBanen->at(j)->getNaam()){
                fVoertuigen->at(i)->setBaanObject(fBanen->at(j));
                found = true;
            }
        }
        if(!found){
            for(unsigned int j = 0; j < fWegenNetwerk->size(); j++){
                if(currentVehicleWay == fWegenNetwerk->at(j)->getNaam()){
                    fVoertuigen->at(i)->setBaanObject(fWegenNetwerk->at(j));
                }
            }
        }

        // Set Last voertuig for ban
        if (fVoertuigen->at(i)->getBaanObject()->getfLastVoertuig() == NULL){
            // First one to be set
            fVoertuigen->at(i)->getBaanObject()->setfLastVoertuig(fVoertuigen->at(i));
        }else{
            // Only change if smaller position
            if (fVoertuigen->at(i)->getPositie() < fVoertuigen->at(i)->getBaanObject()->getfLastVoertuig()->getPositie()){
                fVoertuigen->at(i)->getBaanObject()->setfLastVoertuig(fVoertuigen->at(i));
            }
        }
    }

    for(unsigned int i = 0; i<fVoertuigen->size(); i++){
        ENSURE(fVoertuigen->at(i)->getBaanObject()->getNaam() == fVoertuigen->at(i)->getBaan(),
                   "initializeVehicleBaanObject post condition failure");
    }
}

void System::initializeBaanVerbindingObjects() {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling initializeBaanVerbindingObjects");


    for(unsigned int i = 0; i < fWegenNetwerk->size(); i++){
        bool found = false;
        std::string currentWay = fWegenNetwerk->at(i)->getVerbinding();
        for(unsigned int j = 0; j < fBanen->size(); j++){
            if(currentWay == fBanen->at(j)->getNaam()){
                fWegenNetwerk->at(i)->setVerbindingObject(fBanen->at(j));
                found = true;
            }
        }
        if(!found){
            for(unsigned int j = 0; j < fWegenNetwerk->size(); j++){
                if(currentWay == fWegenNetwerk->at(j)->getNaam()){
                    fWegenNetwerk->at(i)->setVerbindingObject(fWegenNetwerk->at(j));
                }
            }
        }

    }

    for(unsigned int i = 0; i < fWegenNetwerk->size(); i++){
        bool ensure = fWegenNetwerk->at(i)->getVerbindingObject()->getNaam() == fWegenNetwerk->at(i)->getVerbinding();
        ENSURE(ensure,"initializeBaanVerbindingObjects() post condition failure");
    }

}

void System::filterVehicles() {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling filterVehicles");

    std::vector<Voertuig*>* tempVoertuigen = new std::vector<Voertuig*>;

    if(fVoertuigen->size() > 0){
        for(unsigned int i = 0; i < fVoertuigen->size(); i++){
            if(!fVoertuigen->at(i)->isDeleteObject()){//if vehicle is not to be deleted then place this to a vector
                tempVoertuigen->push_back(fVoertuigen->at(i));
            }
        }
        for(unsigned long j = fVoertuigen->size()-1; j > 0; j--){
            if(fVoertuigen->at(j)->isDeleteObject()){
                delete fVoertuigen->at(j);
            }
        }
        delete fVoertuigen;
        fVoertuigen = tempVoertuigen;
    }

    for(unsigned int i = 0; i<fVoertuigen->size(); i++){
        ENSURE(fVoertuigen->at(i)->isDeleteObject() == false,"filterVehicles post condition failure");
    }

}

void System::simpeleUitvoer() const {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling simpeleUitvoer");

    for(unsigned int i = 0; i<fBanen->size(); i++){
        std::cout << "\nBaan: " << fBanen->at(i)->getNaam() << std::endl;
        std::cout << "\t-> lengte:          " << fBanen->at(i)->getLengte() << " m" << std::endl;
        std::cout << "\t-> rijstroken:      " << fBanen->at(i)->getFRijstroken() << std::endl;
        std::cout << "\t-> snelheidslimiet: " << fBanen->at(i)->getSnelheidsLimiet() << " km/h" << std::endl;

        std::cout << std::endl;
        for(unsigned int j = 0; j < fBanen->at(i)->getFVerkeerstekens().size(); j++){
            if (fBanen->at(i)->getFVerkeerstekens().at(j)->getFType() == "ZONE"){
                std::cout << "\t-> " << fBanen->at(i)->getFVerkeerstekens().at(j)->getFType() << ": ";
                std::cout << fBanen->at(i)->getFVerkeerstekens().at(j)->getFSnelheidslimiet() << "km/h (";
                std::cout << fBanen->at(i)->getFVerkeerstekens().at(j)->getFPositie() << "m - ";
                std::cout << fBanen->at(i)->getFVerkeerstekens().at(j)->getFEndPositie() <<  "m)" << std::endl;

            }else{
                std::cout << "\t-> " << fBanen->at(i)->getFVerkeerstekens().at(j)->getFType() << ": ";
                std::cout << fBanen->at(i)->getFVerkeerstekens().at(j)->getFPositie() << "m" << std::endl;
            }
        }
    }
    for(unsigned int i = 0; i<fWegenNetwerk->size(); i++){
        std::cout << "\nBaan: " << fWegenNetwerk->at(i)->getNaam() << std::endl;
        std::cout << "\t-> lengte:          " << fWegenNetwerk->at(i)->getLengte() << " m" << std::endl;
        std::cout << "\t-> rijstroken:      " << fWegenNetwerk->at(i)->getFRijstroken() << std::endl;
        std::cout << "\t-> snelheidslimiet: " << fWegenNetwerk->at(i)->getSnelheidsLimiet() << " km/h" << std::endl;
        std::cout << "\t-> verbinding:      " << fWegenNetwerk->at(i)->getVerbinding() << std::endl;

        std::cout << std::endl;
        for(unsigned int j = 0; j < fWegenNetwerk->at(i)->getFVerkeerstekens().size(); j++){
            if (fWegenNetwerk->at(i)->getFVerkeerstekens().at(j)->getFType() == "ZONE"){
                std::cout << "\t-> " << fWegenNetwerk->at(i)->getFVerkeerstekens().at(j)->getFType() << ": ";
                std::cout << fWegenNetwerk->at(i)->getFVerkeerstekens().at(j)->getFSnelheidslimiet() << "km/h (";
                std::cout << fWegenNetwerk->at(i)->getFVerkeerstekens().at(j)->getFPositie() << "m - ";
                std::cout << fWegenNetwerk->at(i)->getFVerkeerstekens().at(j)->getFEndPositie() <<  "m)" << std::endl;

            }else{
                std::cout << "\t-> "  << fWegenNetwerk->at(i)->getFVerkeerstekens().at(j)->getFType() << ": ";
                std::cout << fWegenNetwerk->at(i)->getFVerkeerstekens().at(j)->getFPositie() << "m" << std::endl;
            }
        }
    }

    for(unsigned int i = 0; i<fVoertuigen->size(); i++){
        std::cout << "\nVoertuig: " << fVoertuigen->at(i)->getType() << " (" << fVoertuigen->at(i)->getNummerPlaat() << ")" << std::endl;
        std::cout << "\t-> baan:            " << fVoertuigen->at(i)->getBaan() << std::endl;
        std::cout << "\t-> positie:         " << fVoertuigen->at(i)->getPositie() << " m" << std::endl;
        std::cout << "\t-> snelheid:        " << fVoertuigen->at(i)->getSnelheid() << " km/h" << std::endl;

        if (fVoertuigen->at(i)->getType() == "BUS" and fVoertuigen->at(i)->getFPauseCounter() != 0){
            std::cout << "\t-> Stoping since:   " <<  30-fVoertuigen->at(i)->getFPauseCounter() << " s" << std::endl;
        }
    }
}

void System::simulate(unsigned int iterations) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling simulate");
    REQUIRE(iterations >= 0, "Iterations must be a positive integer");

    organizeVehicles();
    initializeVehicleBaanObject();
    initializeBaanVerbindingObjects();

    for(unsigned int i = 0; i < iterations; i++){
        for(unsigned int j = 0; j < fVoertuigen->size(); j ++){
            fVoertuigen->at(j)->updatePosition();
        }
        //remove to be deleted vehicles
        filterVehicles();
    }
}


void System::automaticSimulation(std::string type, std::string fileName,int factor,int time) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling automaticSimulation");
    REQUIRE(time >= 0, "When calling automaticSimulation() the parameter time must be a non negative number");
    REQUIRE(factor <= getLengthOfShortestBaan()/2, "When calling automaticSimulation() the factor must be bigger or equal than half of the shortest baan length");
    REQUIRE(fileName != "", "automaticSimulation() pre condition failure. Invalid fileName");

    for(unsigned int i = 0; i < fBanen->size(); i++){
        fBanen->at(i)->sortVerkeersteken();
        fBanen->at(i)->assignZoneLimit();
    }
    for(unsigned int i = 0; i < fWegenNetwerk->size(); i++){
        fWegenNetwerk->at(i)->sortVerkeersteken();
        fWegenNetwerk->at(i)->assignZoneLimit();
    }

    // Clean file if we print to the file
    if( type != "simpele"){
        // Clean the standard file
        std::ofstream myfile;
        std::string fname = fileName+".txt";
        myfile.open (fname.c_str());
        myfile << "";
        myfile.close();
    }

    while(fVoertuigen->size()>0){
        simulate();
        counter++;
        if (type == "simpele"){
            std::cout << std::endl << "#=======================================#" << std::endl;
            simpeleUitvoer();
        }else{
            grafischeImpressie(fileName, factor, time);
        }
    }
}

bool System::properlyInitialized() const{
    return _initCheck == this;
}

bool System::compareFiles(const std::string &p1, const std::string &p2) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling compareFiles");

    // File compare
    // Source: https://stackoverflow.com/a/37575457/8076979
    std::ifstream f1(p1.c_str(), std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2.c_str(), std::ifstream::binary|std::ifstream::ate);

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

void System::grafischeImpressie(std::string name, int factor, int time) {

    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling grafischeImpressie");
    REQUIRE(time >= 0, "When calling grafischeImpressie() the parameter time must be a non negative number");
    REQUIRE(factor <= getLengthOfShortestBaan()/2, "When calling grafischeImpressie() the factor must be bigger or equal than half of the shortest baan length");
    REQUIRE(name != "", "grafischeImpressie() pre condition failure. Invalid name");

    if(time == 0 or time == counter){
        std::string output;
        // Organize Vehicles is needed as a vehicle could have changed the baan in the last iteration of simulation
        organizeVehicles();

        // Convert int to string
        std::string count;
        std::ostringstream convert;
        convert << counter;
        count = convert.str();

        output += ("\nSystem after: " + count + " s\n");

        // Output the Banen
        for (unsigned int i = 0; i < fBanen->size(); i++){
            std::pair<std::string,std::string> verkeerstekenOutput = outputVerkeersteken(fBanen->at(i),factor);
            output += (fBanen->at(i)->getNaam() + " | " + verkeerstekenOutput.first + "\n");
            output += (fBanen->at(i)->getNaam() + " | " + verkeerstekenOutput.second + "\n");
            output += (fBanen->at(i)->getNaam() + " | " + outputBaan(fBanen->at(i),factor) + "\n");

            for (unsigned int j = 1; j < fBanen->at(i)->getFRijstroken(); j++){
                output += (fBanen->at(i)->getNaam() + " | " + std::string(fBanen->at(i)->getLengte()/factor,'=') + "\n");
            }
        }

        // Ouput the Netwerken
        for (unsigned int i = 0; i < fWegenNetwerk->size(); i++) {
            std::pair<std::string,std::string> verkeerstekenOutput = outputVerkeersteken(fWegenNetwerk->at(i),factor);
            output += (fWegenNetwerk->at(i)->getNaam() + " | " + verkeerstekenOutput.first + "\n");
            output += (fWegenNetwerk->at(i)->getNaam() + " | " + verkeerstekenOutput.second + "\n");
            output += (fWegenNetwerk->at(i)->getNaam() + " | " + outputBaan(fWegenNetwerk->at(i),factor) + "\n");

            // Draw the extra rijstroken
            for (unsigned int j = 1; j < fWegenNetwerk->at(i)->getFRijstroken(); j++){
                output += (fWegenNetwerk->at(i)->getNaam() + " | " + std::string(fWegenNetwerk->at(i)->getLengte()/factor,'=') + "\n");
            }
        }

        // Write to file
        std::ofstream myfile;
        std::string fname = name+".txt";
        myfile.open (fname.c_str(),std::fstream::app);
        myfile << output;
        myfile.close();

    }
}

std::string System::outputBaan(Baan *baan, int factor) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling outputBaan");
    REQUIRE(factor <= baan->getLengte()/2, "When calling outputBaan() the factor must be bigger or equal than half of baan length");

    std::string baanOutput = std::string(baan->getLengte()/factor,'=');
    // Loop over all cars
    Voertuig* current = baan->getfLastVoertuig();
    while (current != NULL){
        bool possible = false;
        int bias = 0;
        while(!possible){
            // Check that we aren't out of bounds
            if (current->getPositie() / factor + bias < baanOutput.size()){
                if (baanOutput[current->getPositie() / factor + bias] == '=') {
                    possible = true;
                    baanOutput[current->getPositie() / factor + bias] = current->getType()[0];
                } else {
                    bias++;
                }
            }else{
                baanOutput[baanOutput.size()-1] = current->getType()[0];
                possible = true;
            }
        }
        current = current->getNextVoertuig();
    }

    return baanOutput;
}

std::pair<std::string, std::string> System::outputVerkeersteken(Baan *baan, int factor) {
    REQUIRE(this->properlyInitialized(), "System wasn't initialized when calling outputVerkeersteken");
    REQUIRE(factor <= baan->getLengte()/2, "When calling outputVerkeersteken() the factor must be bigger or equal than half of baan length");

    std::string zones = std::string(baan->getLengte()/factor,'_');
    std::string bushalte = std::string(baan->getLengte()/factor,'_');

    for(unsigned int j = 0; j < baan->getFVerkeerstekens().size(); j++){

        Verkeersteken* current = baan->getFVerkeerstekens().at(j);
        bool possible = false;
        int bias = 0;
        while(!possible){

            // Check the type
            if (current->getFType() == "ZONE"){
                // Check that we aren't out of bounds
                if (current->getFPositie() / factor + bias < bushalte.size()){
                    if(zones[current->getFPositie()/factor+bias] == '_'){
                        possible = true;
                        zones[current->getFPositie()/factor+bias] = 'Z';
                    }else{
                        bias++;
                    }
                }else{
                    zones[zones.size()-1] = 'Z';
                    possible = true;
                }
            }else {

                //TODO Adjust to represent the actual length of the Bus stop

                // Check that we aren't out of bounds
                if (current->getFPositie() / factor + bias < bushalte.size()){
                    if (bushalte[current->getFPositie() / factor + bias] == '_') {
                        possible = true;
                        bushalte[current->getFPositie() / factor + bias] = 'B';
                    } else {
                        bias++;
                    }
                }else{
                    bushalte[bushalte.size()-1] = 'B';
                    possible = true;
                }
            }
        }
    }

    return std::make_pair(zones,bushalte);
}

int System::getLengthOfShortestBaan() const {
    int smallest = 2;
    for(unsigned int i = 0; i < getBanen()->size(); i++){
        if (getBanen()->at(i)->getLengte() < smallest or smallest == 2){
            smallest = getBanen()->at(i)->getLengte();
        }
    }

    for(unsigned int i = 0; i < getWegenNetwerk()->size(); i++){
        if (getWegenNetwerk()->at(i)->getLengte() < smallest or smallest == 2){
            smallest = getWegenNetwerk()->at(i)->getLengte();
        }
    }

    return smallest;
}