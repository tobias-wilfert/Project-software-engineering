//============================================================================
// Name        : BaanTest.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "SystemDebug.h"
#include "../XmlParser.h"

class BaanTest: public ::testing::Test {
protected:
    friend class SystemDebug;
    friend class XmlParser;
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
    //TODO: May not work seems fish
    XmlParser parser  = XmlParser("GetterAndSetterTester.xml");
    XmlParser parser1 = XmlParser("OneWegenNetwerk.xml");
};


//////////////////////  BAAN TEST BEGINS HERE  /////////////////////////////////
//test xml file with duplicate Banen objects
TEST_F(BaanTest, VierBanenVierDuplicaten){
    XmlParser parser4("DuplicateBanen4Banen4Duplicaten.xml");
    EXPECT_EQ(parser4.getBanen()->size(), 1);
}

TEST_F(BaanTest, VierBanenTweeDuplicaten){
    XmlParser parser4("DuplicateBanen4Banen2Duplicaten.xml");
    EXPECT_EQ(parser4.getBanen()->size(), 2);
}

//test getters and setters of Banen + randgevallen
TEST_F(BaanTest, BanenGetNaam){
    EXPECT_EQ(parser.getBanen()->at(0)->getNaam(), "E20");
}
TEST_F(BaanTest, BanenSetNaam){
    parser.getBanen()->at(0)->setNaam("E22");
    EXPECT_EQ(parser.getBanen()->at(0)->getNaam(), "E22");
}
TEST_F(BaanTest, BanenSetNaamRandgeval){
    //EXPECT_EXIT(parser.getBanen()->at(0)->setNaam(""), ::testing::ExitedWithCode(6), "");
    EXPECT_DEATH(parser.getBanen()->at(0)->setNaam(""), "");
}
TEST_F(BaanTest, BanenGetLengte){
    EXPECT_EQ(parser.getBanen()->at(0)->getLengte(), 1000);
}
TEST_F(BaanTest, BanensetLengte){
    parser.getBanen()->at(0)->setLengte(1111);
    EXPECT_EQ(parser.getBanen()->at(0)->getLengte(), 1111);
}
TEST_F(BaanTest, BanensetLengteRandgeval){
    EXPECT_DEATH(parser.getBanen()->at(0)->setLengte(-1), "");
}
TEST_F(BaanTest, BanenGetSnelheidsLimiet){
    EXPECT_EQ(parser.getBanen()->at(0)->getSnelheidsLimiet(), 100);
}
TEST_F(BaanTest, BanenSetSnelheidsLimiet){
    parser.getBanen()->at(0)->setSnelheidsLimiet(150);
    EXPECT_EQ(parser.getBanen()->at(0)->getSnelheidsLimiet(), 150);
}
TEST_F(BaanTest, BanenSetSnelheidsLimietRandgeval0){
    EXPECT_DEATH(parser.getBanen()->at(0)->setSnelheidsLimiet(-23), "");
}
TEST_F(BaanTest, BanenSetSnelheidsLimietRandgeval1){
    EXPECT_DEATH(parser.getBanen()->at(0)->setSnelheidsLimiet(0), "");
}
TEST_F(BaanTest, BanenGetVerbindingWithoutVerbinding){
    EXPECT_EQ(parser.getBanen()->at(0)->getVerbinding(), "");
}

TEST_F(BaanTest, BanenGetVerbindingWithVerbinding){
    EXPECT_EQ(parser1.getWegenNetwerk()->at(0)->getVerbinding(), "E20");
}
TEST_F(BaanTest, BanenSetVerbinding){
    parser1.getWegenNetwerk()->at(0)->setVerbinding("E30");
    EXPECT_EQ(parser1.getWegenNetwerk()->at(0)->getVerbinding(), "E30");
}
TEST_F(BaanTest, BanenSetVerbindingRandGeval){
    EXPECT_DEATH(parser1.getWegenNetwerk()->at(0)->setVerbinding(""), "");
}

TEST_F(BaanTest, BanenGetVerbindingObject){
    XmlParser parser2("OneWegenNetwerk.xml");
    SystemDebug systemTest(parser2.getBanen(),parser2.getWegenNetwerk(),parser2.getVoertuigen());
    systemTest.initializeBaanVerbindingObjects();
    EXPECT_EQ(systemTest.getWegenNetwerk()->at(0)->getVerbindingObject(), systemTest.getBanen()->at(0));
}
