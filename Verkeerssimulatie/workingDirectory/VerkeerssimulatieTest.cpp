//============================================================================
// Name        : Verkeerssimulatie.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "XmlParser.h"
#include "SystemTesterFile.h"
class VerkeerssimulatieTest: public ::testing::Test {
protected:
    friend class XmlParser;
    friend class System;
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
// Tests the default constructor.
TEST_F(VerkeerssimulatieTest, DefaultConstructor) {

    XmlParser parser("Wegen_en_voertuigen.xml");

    EXPECT_TRUE((parser.properlyInitialized()));
    EXPECT_TRUE((parser.getBanen()->size() > 0));

    EXPECT_TRUE((parser.getVoertuigen()->size() > 0));
    EXPECT_TRUE((parser.getWegenNetwerk()->size() >= 0));
}

// Can't work with non existing file
TEST_F(VerkeerssimulatieTest, ConstructorWithNoneFile) {
    //EXPECT_DEATH(XmlParser parser(""),"");
    EXPECT_EXIT(XmlParser parser(""), ::testing::ExitedWithCode(1), "");

}

// Can't work with non XML File
TEST_F(VerkeerssimulatieTest, ConstructorWithNonXMLFile) {
    //EXPECT_DEATH(XmlParser parser("File.txt"),"");
    EXPECT_EXIT(XmlParser parser("File.xml"), ::testing::ExitedWithCode(1), "");

}

// Can't work with empty XML File
TEST_F(VerkeerssimulatieTest, ConstructorWithEmptyXMLFile) {
    //EXPECT_DEATH(XmlParser parser("Empty.xml"),"");
    EXPECT_EXIT(XmlParser parser("Empty.xml"), ::testing::ExitedWithCode(1), "");

}

// Can't work with wrongly XML File
TEST_F(VerkeerssimulatieTest, ConstructorWithWronglyXMLFile) {
    //EXPECT_DEATH(XmlParser parser("Wrong.xml"),"");

    EXPECT_EXIT(XmlParser parser("Wrong.xml"), ::testing::ExitedWithCode(1), "");
}


//////////////////////  BAAN TEST BEGINS HERE  /////////////////////////////////
//test xml file with duplicate Banen objects
TEST_F(VerkeerssimulatieTest, VierBanenVierDuplicaten){
    XmlParser parser("DuplicateBanen4Banen4Duplicaten.xml");
    EXPECT_EQ(parser.getBanen()->size(), 1);
}

TEST_F(VerkeerssimulatieTest, VierBanenTweeDuplicaten){
    XmlParser parser("DuplicateBanen4Banen2Duplicaten.xml");
    EXPECT_EQ(parser.getBanen()->size(), 2);
}

//test getters and setters of Banen + randgevallen
XmlParser parser("GetterAndSetterTester.xml");
TEST_F(VerkeerssimulatieTest, BanenGetNaam){
    EXPECT_EQ(parser.getBanen()->at(0)->getNaam(), "E20");
}
TEST_F(VerkeerssimulatieTest, BanenSetNaam){
    parser.getBanen()->at(0)->setNaam("E22");
    EXPECT_EQ(parser.getBanen()->at(0)->getNaam(), "E22");
}
TEST_F(VerkeerssimulatieTest, BanenSetNaamRandgeval){
    //EXPECT_EXIT(parser.getBanen()->at(0)->setNaam(""), ::testing::ExitedWithCode(6), "");
    EXPECT_DEATH(parser.getBanen()->at(0)->setNaam(""), "");
}
TEST_F(VerkeerssimulatieTest, BanenGetLengte){
    EXPECT_EQ(parser.getBanen()->at(0)->getLengte(), 1000);
}
TEST_F(VerkeerssimulatieTest, BanensetLengte){
    parser.getBanen()->at(0)->setLengte(1111);
    EXPECT_EQ(parser.getBanen()->at(0)->getLengte(), 1111);
}
TEST_F(VerkeerssimulatieTest, BanensetLengteRandgeval){
    EXPECT_DEATH(parser.getBanen()->at(0)->setLengte(-1), "");
}
TEST_F(VerkeerssimulatieTest, BanenGetSnelheidsLimiet){
    EXPECT_EQ(parser.getBanen()->at(0)->getSnelheidsLimiet(), 100);
}
TEST_F(VerkeerssimulatieTest, BanenSetSnelheidsLimiet){
    parser.getBanen()->at(0)->setSnelheidsLimiet(150);
    EXPECT_EQ(parser.getBanen()->at(0)->getSnelheidsLimiet(), 150);
}
TEST_F(VerkeerssimulatieTest, BanenSetSnelheidsLimietRandgeval0){
    EXPECT_DEATH(parser.getBanen()->at(0)->setSnelheidsLimiet(-23), "");
}
TEST_F(VerkeerssimulatieTest, BanenSetSnelheidsLimietRandgeval1){
    EXPECT_DEATH(parser.getBanen()->at(0)->setSnelheidsLimiet(0), "");
}
TEST_F(VerkeerssimulatieTest, BanenGetVerbindingWithoutVerbinding){
    EXPECT_EQ(parser.getBanen()->at(0)->getVerbinding(), "");
}
XmlParser parser1("OneWegenNetwerk.xml");
TEST_F(VerkeerssimulatieTest, BanenGetVerbindingWithVerbinding){
    EXPECT_EQ(parser1.getWegenNetwerk()->at(0)->getVerbinding(), "E20");
}
TEST_F(VerkeerssimulatieTest, BanenSetVerbinding){
    parser1.getWegenNetwerk()->at(0)->setVerbinding("E30");
    EXPECT_EQ(parser1.getWegenNetwerk()->at(0)->getVerbinding(), "E30");
}
TEST_F(VerkeerssimulatieTest, BanenSetVerbindingRandGeval){
    EXPECT_DEATH(parser1.getWegenNetwerk()->at(0)->setVerbinding(""), "");
}


TEST_F(VerkeerssimulatieTest, BanenGetVerbindingObject){
    XmlParser parser2("OneWegenNetwerk.xml");
    System systemTest(parser2.getBanen(),parser2.getWegenNetwerk(),parser2.getVoertuigen());
    systemTest.initializeBaanVerbindingObjects();
    EXPECT_EQ(systemTest.getWegenNetwerk()->at(0)->getVerbindingObject(), systemTest.getBanen()->at(0));
}
/////////////////////////////////END BAAN TESTS HERE//////////////////////////////////////////////////////


/////////////////////////////////Begin System Tests////////////////////////////////////////////////////

TEST_F(VerkeerssimulatieTest, organizeVehicles){
    XmlParser parser3("SYSTEMorganizeVehiclesTest.xml");
    System s(parser3.getBanen(), parser3.getWegenNetwerk(), parser3.getVoertuigen());
    Voertuig *nullpointer = NULL;  //nullpointer van Object Voertuig
    EXPECT_EQ(s.getVoertuigen()->at(0)->getFNextVoertuig(), nullpointer);
    EXPECT_EQ(s.getVoertuigen()->at(1)->getFNextVoertuig(), nullpointer);
    EXPECT_EQ(s.getVoertuigen()->at(2)->getFNextVoertuig(), nullpointer);
    EXPECT_EQ(s.getVoertuigen()->at(3)->getFNextVoertuig(), nullpointer);

    s.organizeVehicles();

    EXPECT_EQ(s.getVoertuigen()->at(0)->getFNextVoertuig()->getNummerPlaat(), "651BUFF");
    EXPECT_EQ(s.getVoertuigen()->at(1)->getFNextVoertuig()->getNummerPlaat(), "1THK180");
    EXPECT_EQ(s.getVoertuigen()->at(2)->getFNextVoertuig()->getNummerPlaat(), "651BUFFF");
    EXPECT_EQ(s.getVoertuigen()->at(3)->getFNextVoertuig(), nullpointer);

    EXPECT_EQ(s.getVoertuigen()->at(0)->getPositie(), 10);
    EXPECT_EQ(s.getVoertuigen()->at(1)->getPositie(), 0);
    EXPECT_EQ(s.getVoertuigen()->at(2)->getPositie(), 15);
    EXPECT_EQ(s.getVoertuigen()->at(3)->getPositie(), 1990);
}


TEST_F(VerkeerssimulatieTest, initializeVehicleBaanObject){
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

TEST_F(VerkeerssimulatieTest, initializeBaanVerbindingObjects){
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
TEST_F(VerkeerssimulatieTest, filterVehicles){
    EXPECT_EQ(s1.getVoertuigen()->size(), 4);
    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    EXPECT_EQ(s1.getVoertuigen()->size(), 3);
    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    EXPECT_EQ(s1.getVoertuigen()->size(), 2);
    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    EXPECT_EQ(s1.getVoertuigen()->size(), 1);

    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    EXPECT_EQ(s1.getVoertuigen()->size(), 0);

}

XmlParser parser7("SYSTEMgetBanenEnWegenNetwerkTest.xml");
System s2(parser7.getBanen(), parser7.getWegenNetwerk(), parser7.getVoertuigen());
TEST_F(VerkeerssimulatieTest, getBanen){
    EXPECT_EQ(s2.getBanen()->size(), 4);
    EXPECT_EQ(s2.getBanen()->at(0)->getNaam(), "E10");
    EXPECT_EQ(s2.getBanen()->at(1)->getNaam(), "E20");
    EXPECT_EQ(s2.getBanen()->at(2)->getNaam(), "E30");
    EXPECT_EQ(s2.getBanen()->at(3)->getNaam(), "E40");
}

TEST_F(VerkeerssimulatieTest, getWegenNetwerk){
    EXPECT_EQ(s2.getWegenNetwerk()->size(), 5);
    EXPECT_EQ(s2.getWegenNetwerk()->at(0)->getNaam(), "E60");
    EXPECT_EQ(s2.getWegenNetwerk()->at(1)->getNaam(), "E70");
    EXPECT_EQ(s2.getWegenNetwerk()->at(2)->getNaam(), "E80");
    EXPECT_EQ(s2.getWegenNetwerk()->at(3)->getNaam(), "E90");
    EXPECT_EQ(s2.getWegenNetwerk()->at(4)->getNaam(), "E100");
}


XmlParser parser8("SYSTEMsimulateTest.xml");
System s3(parser8.getBanen(), parser8.getWegenNetwerk(), parser8.getVoertuigen());
TEST_F(VerkeerssimulatieTest, simulate){
    EXPECT_EQ(s3.getVoertuigen()->at(0)->getSnelheid(), 0);
    EXPECT_EQ(s3.getVoertuigen()->at(1)->getSnelheid(), 0);
    EXPECT_EQ(s3.getVoertuigen()->at(2)->getSnelheid(), 0);
    EXPECT_EQ(s3.getVoertuigen()->at(3)->getSnelheid(), 0);

    EXPECT_EQ(s3.getVoertuigen()->at(0)->getPositie(), 10);
    EXPECT_EQ(s3.getVoertuigen()->at(1)->getPositie(), 0);
    EXPECT_EQ(s3.getVoertuigen()->at(2)->getPositie(), 15);
    EXPECT_EQ(s3.getVoertuigen()->at(3)->getPositie(), 1990);

    s3.simulate();

    EXPECT_EQ(s3.getVoertuigen()->at(0)->getSnelheid(), 0);
    EXPECT_EQ(s3.getVoertuigen()->at(1)->getSnelheid(), 1);
    EXPECT_EQ(s3.getVoertuigen()->at(2)->getSnelheid(), 2);
    EXPECT_EQ(s3.getVoertuigen()->at(3)->getSnelheid(), 2);

    EXPECT_EQ(s3.getVoertuigen()->at(0)->getPositie(), 10);
    EXPECT_EQ(s3.getVoertuigen()->at(1)->getPositie(), 1);
    EXPECT_EQ(s3.getVoertuigen()->at(2)->getPositie(), 17);
    EXPECT_EQ(s3.getVoertuigen()->at(3)->getPositie(), 1992);

    s3.simulate();

    EXPECT_EQ(s3.getVoertuigen()->at(0)->getSnelheid(), 0);
    EXPECT_EQ(s3.getVoertuigen()->at(1)->getSnelheid(), 1.125);
    EXPECT_EQ(s3.getVoertuigen()->at(2)->getSnelheid(), 4);
    EXPECT_EQ(s3.getVoertuigen()->at(3)->getSnelheid(), 4);

    EXPECT_EQ(s3.getVoertuigen()->at(0)->getPositie(), 10);
    EXPECT_EQ(s3.getVoertuigen()->at(1)->getPositie(), 2.125);
    EXPECT_EQ(s3.getVoertuigen()->at(2)->getPositie(), 21);
    EXPECT_EQ(s3.getVoertuigen()->at(3)->getPositie(), 1996);

    EXPECT_EQ(s3.getVoertuigen()->size(), 4);

    s3.simulate();

    EXPECT_EQ(s3.getVoertuigen()->size(), 3);

    s3.simulate(43);
    EXPECT_EQ(s3.getVoertuigen()->size(), 2);

    s3.simulate(3);
    EXPECT_EQ(s3.getVoertuigen()->size(), 1);

    s3.simulate(4);
    EXPECT_EQ(s3.getVoertuigen()->size(), 0);
}
XmlParser parser9("SYSTEMsimulateTest.xml");
System s4(parser9.getBanen(), parser9.getWegenNetwerk(), parser9.getVoertuigen());
TEST_F(VerkeerssimulatieTest, automaticSimulation){
    EXPECT_EQ(s4.getVoertuigen()->size(), 4);

    s4.automaticSimulation();
    EXPECT_EQ(s4.getVoertuigen()->size(), 0);
}
int main(int argc, char **argv) {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

