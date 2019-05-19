//============================================================================
// Name        : SystemTest.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "../System.h"
#include "../XmlParser.h"

class SystemTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.

};

/////////////////////////////////Begin System Tests////////////////////////////////////////////////////

TEST_F(SystemTest, organizeVehicles){
    XmlParser parser3("SYSTEMorganizeVehiclesTest.xml");
    System s(parser3.getBanen(), parser3.getWegenNetwerk(), parser3.getVoertuigen());
    Voertuig *nullpointer = NULL;  //nullpointer van Object Voertuig
    EXPECT_EQ(s.getVoertuigen()->at(0)->getNextVoertuig(), nullpointer);
    EXPECT_EQ(s.getVoertuigen()->at(1)->getNextVoertuig(), nullpointer);
    EXPECT_EQ(s.getVoertuigen()->at(2)->getNextVoertuig(), nullpointer);
    EXPECT_EQ(s.getVoertuigen()->at(3)->getNextVoertuig(), nullpointer);

    s.organizeVehicles();

    EXPECT_EQ(s.getVoertuigen()->at(0)->getNextVoertuig()->getNummerPlaat(), "651BUFF");
    EXPECT_EQ(s.getVoertuigen()->at(1)->getNextVoertuig()->getNummerPlaat(), "1THK180");
    EXPECT_EQ(s.getVoertuigen()->at(2)->getNextVoertuig()->getNummerPlaat(), "651BUFFF");
    EXPECT_EQ(s.getVoertuigen()->at(3)->getNextVoertuig(), nullpointer);

    EXPECT_EQ(s.getVoertuigen()->at(0)->getPositie(), 10);
    EXPECT_EQ(s.getVoertuigen()->at(1)->getPositie(), 0);
    EXPECT_EQ(s.getVoertuigen()->at(2)->getPositie(), 15);
    EXPECT_EQ(s.getVoertuigen()->at(3)->getPositie(), 1990);
}


TEST_F(SystemTest, initializeVehicleBaanObject){
    XmlParser parser4("SYSTEMinitializeVehicleBaanObjectTest.xml");
    System s1(parser4.getBanen(), parser4.getWegenNetwerk(), parser4.getVoertuigen());
    Baan *nullpointer = NULL;
    EXPECT_EQ(s1.getVoertuigen()->at(0)->getBaanObject(), nullpointer);
    EXPECT_EQ(s1.getVoertuigen()->at(1)->getBaanObject(), nullpointer);
    EXPECT_EQ(s1.getVoertuigen()->at(2)->getBaanObject(), nullpointer);
    EXPECT_EQ(s1.getVoertuigen()->at(3)->getBaanObject(), nullpointer);
    s1.initializeVehicleBaanObject();
    EXPECT_EQ(s1.getVoertuigen()->at(0)->getBaanObject(), s1.getBanen()->at(3));
    EXPECT_EQ(s1.getVoertuigen()->at(1)->getBaanObject(), s1.getBanen()->at(0));
    EXPECT_EQ(s1.getVoertuigen()->at(2)->getBaanObject(), s1.getBanen()->at(1));
    EXPECT_EQ(s1.getVoertuigen()->at(3)->getBaanObject(), s1.getBanen()->at(2));
}

XmlParser parser5("SYSTEMinitializeBaanVerbindingObjectsTest.xml");
System s = System(parser5.getBanen(), parser5.getWegenNetwerk(), parser5.getVoertuigen());

TEST_F(SystemTest, initializeBaanVerbindingObjects){
    Baan *nullpointer = NULL;
    EXPECT_EQ(s.getBanen()->at(0)->getVerbindingObject(), nullpointer);
    EXPECT_EQ(s.getWegenNetwerk()->at(0)->getVerbindingObject(), nullpointer);
    EXPECT_EQ(s.getWegenNetwerk()->at(1)->getVerbindingObject(), nullpointer);
    EXPECT_EQ(s.getWegenNetwerk()->at(2)->getVerbindingObject(), nullpointer);
    EXPECT_EQ(s.getWegenNetwerk()->at(3)->getVerbindingObject(), nullpointer);
    EXPECT_EQ(s.getWegenNetwerk()->at(4)->getVerbindingObject(), nullpointer);

    s.initializeBaanVerbindingObjects();

    EXPECT_EQ(s.getWegenNetwerk()->at(0)->getVerbindingObject(), s.getWegenNetwerk()->at(3));
    EXPECT_EQ(s.getWegenNetwerk()->at(1)->getVerbindingObject(), s.getWegenNetwerk()->at(0));
    EXPECT_EQ(s.getWegenNetwerk()->at(2)->getVerbindingObject(), s.getWegenNetwerk()->at(4));
    EXPECT_EQ(s.getWegenNetwerk()->at(3)->getVerbindingObject(), s.getWegenNetwerk()->at(1));
    EXPECT_EQ(s.getWegenNetwerk()->at(4)->getVerbindingObject(), s.getWegenNetwerk()->at(2));
}

XmlParser parser6("SYSTEMfilterVehiclesTest.xml");
System s1(parser6.getBanen(), parser6.getWegenNetwerk(), parser6.getVoertuigen());
TEST_F(SystemTest, filterVehicles){
    unsigned int x = 4;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);
    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    x = 3;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);
    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    x = 2;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);
    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    x = 1;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);

    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    x = 0;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);

}

XmlParser parser7("SYSTEMgetBanenEnWegenNetwerkTest.xml");
System s2(parser7.getBanen(), parser7.getWegenNetwerk(), parser7.getVoertuigen());
TEST_F(SystemTest, getBanen){
    unsigned int x = 4;
    EXPECT_EQ(s2.getBanen()->size(), x);
    EXPECT_EQ(s2.getBanen()->at(0)->getNaam(), "E10");
    EXPECT_EQ(s2.getBanen()->at(1)->getNaam(), "E20");
    EXPECT_EQ(s2.getBanen()->at(2)->getNaam(), "E30");
    EXPECT_EQ(s2.getBanen()->at(3)->getNaam(), "E40");
}

TEST_F(SystemTest, getWegenNetwerk){
    unsigned int x = 5;
    EXPECT_EQ(s2.getWegenNetwerk()->size(), x);
    EXPECT_EQ(s2.getWegenNetwerk()->at(0)->getNaam(), "E60");
    EXPECT_EQ(s2.getWegenNetwerk()->at(1)->getNaam(), "E70");
    EXPECT_EQ(s2.getWegenNetwerk()->at(2)->getNaam(), "E80");
    EXPECT_EQ(s2.getWegenNetwerk()->at(3)->getNaam(), "E90");
    EXPECT_EQ(s2.getWegenNetwerk()->at(4)->getNaam(), "E100");
}

XmlParser parser8("SYSTEMsimulateTest.xml");
System s3(parser8.getBanen(), parser8.getWegenNetwerk(), parser8.getVoertuigen());

//TODO Uncomment when updat eposition is working
/*
TEST_F(SystemTest, automaticSimulation){
    unsigned int x = 6;
    EXPECT_EQ(s3.getVoertuigen()->size(), x);

    // Write the output to a file to comapare them later
    std::string output;
    s3.automaticSimulation(output);

    x = 0;
    EXPECT_EQ(s3.getVoertuigen()->size(), x);
}


/////////////////////////////////Test output of entire sysytem////////////////////////////////////////////////////

TEST_F(SystemTest, entireSysytem_Traffic_Jam){
    XmlParser parser("Traffic_Jam.xml");
    System s(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Write the output to a file to comapare them later
    std::string output;
    s.automaticSimulation(output);

    // Write to file
    std::ofstream myfile;
    myfile.open ("Test_Result.txt");
    myfile << output;
    myfile.close();

    // Check the output
    EXPECT_TRUE(s.compareFiles("Test_Result.txt","Traffic_Jam.txt"));
}

TEST_F(SystemTest, entireSysytem_Friday_Night){
    XmlParser parser("Friday_Night.xml");
    System s(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Write the output to a file to comapare them later
    std::string output;
    s.automaticSimulation(output);

    // Write to file
    std::ofstream myfile;
    myfile.open ("Test_Result.txt");
    myfile << output;
    myfile.close();

    // Check the output
    EXPECT_TRUE(s.compareFiles("Test_Result.txt","Friday_Night.txt"));
}

TEST_F(SystemTest, entireSysytem_Holiday){
    XmlParser parser("Holiday.xml");
    System s(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Write the output to a file to comapare them later
    std::string output;
    s.automaticSimulation(output);

    // Write to file
    std::ofstream myfile;
    myfile.open ("Test_Result.txt");
    myfile << output;
    myfile.close();

    // Check the output
    EXPECT_TRUE(s.compareFiles("Test_Result.txt","Holiday.txt"));
}

TEST_F(SystemTest, entireSysytem_Monday_Morning){
    XmlParser parser("Monday_Morning.xml");
    System s(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Write the output to a file to comapare them later
    std::string output;
    s.automaticSimulation(output);

    // Write to file
    std::ofstream myfile;
    myfile.open ("Test_Result.txt");
    myfile << output;
    myfile.close();

    // Check the output
    EXPECT_TRUE(s.compareFiles("Test_Result.txt","Monday_Morning.txt"));
}

TEST_F(SystemTest, entireSysytem_Wednesday_Night){
    XmlParser parser("Wednesday_Night.xml");
    System s(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Write the output to a file to comapare them later
    std::string output;
    s.automaticSimulation(output);

    // Write to file
    std::ofstream myfile;
    myfile.open ("Test_Result.txt");
    myfile << output;
    myfile.close();

    // Check the output
    EXPECT_TRUE(s.compareFiles("Test_Result.txt","Wednesday_Night.txt"));
}

TEST_F(SystemTest, entireSysytem_Wegen_en_voertuigen){
    XmlParser parser("Wegen_en_voertuigen.xml");
    System s(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Write the output to a file to comapare them later
    std::string output;
    s.automaticSimulation(output);

    // Write to file
    std::ofstream myfile;
    myfile.open ("Test_Result.txt");
    myfile << output;
    myfile.close();

    // Check the output
    EXPECT_TRUE(s.compareFiles("Test_Result.txt","Wegen_en_voertuigen.txt"));
}
 */