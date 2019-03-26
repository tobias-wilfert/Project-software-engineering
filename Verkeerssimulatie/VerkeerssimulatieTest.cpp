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
#include "System.h"


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
public:
    XmlParser parser2 = XmlParser("OneWegenNetwerk.xml");
    System systemTest = System(parser2.getBanen(),parser2.getWegenNetwerk(),parser2.getVoertuigen());
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
/*
XmlParser parser2("OneWegenNetwerk.xml");
System systemTest = System(parser2.getBanen(),parser2.getWegenNetwerk(),parser2.getVoertuigen());
TEST_F(VerkeerssimulatieTest, BanenGetVerbindingObject){

    EXPECT_EQ(systemTest.getWegenNetwerk()->at(0)->getVerbindingObject(), systemTest.getBanen()->at(0));
}*/

int main(int argc, char **argv) {
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

