//============================================================================
// Name        : BaanTest.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "../System.h"
#include "../XmlParser.h"

class BaanTest: public ::testing::Test {
protected:

    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {}

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }
};


//////////////////////  BAAN TEST BEGINS HERE  /////////////////////////////////
//test xml file with duplicate Banen objects

XmlParser parser = XmlParser("Parser/GetterAndSetterTester.xml");
XmlParser parser1 = XmlParser("Parser/OneWegenNetwerk.xml");
unsigned int x = 1;

TEST_F(BaanTest, VierBanenVierDuplicaten){
    XmlParser parser4("Parser/DuplicateBanen4Banen4Duplicaten.xml");
    EXPECT_EQ(parser4.getBanen()->size(), x);
}

TEST_F(BaanTest, VierBanenTweeDuplicaten){
    XmlParser parser4("Parser/DuplicateBanen4Banen2Duplicaten.xml");
    x = 2;
    EXPECT_EQ(parser4.getBanen()->size(), x);
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
    XmlParser parser2("Parser/OneWegenNetwerk.xml");
    System systemTest(parser2.getBanen(),parser2.getWegenNetwerk(),parser2.getVoertuigen());
    systemTest.initializeBaanVerbindingObjects();
    EXPECT_EQ(systemTest.getWegenNetwerk()->at(0)->getVerbindingObject(), systemTest.getBanen()->at(0));
}

/// Tests 2.0

Baan b = Baan();

TEST_F(BaanTest, Baan_setFRijstroken_postcondition){
    b.setFRijstroken(10);
    EXPECT_TRUE(10 == b.getFRijstroken());
}

TEST_F(BaanTest,addFVerkeersteken_precondition){
    Verkeersteken* v = NULL;
    EXPECT_DEATH(b.addFVerkeersteken(v),"");
}

TEST_F(BaanTest,addFVerkeersteken_postcondition){
    Verkeersteken* v = new Verkeersteken();
    b.addFVerkeersteken(v);
    EXPECT_TRUE(v == b.getFVerkeerstekens().back());
}

/// Tests 3.0
TEST_F(BaanTest, Baan_setfLastVoertuig_postcondition){
    Voertuig* v = new Voertuig;
    b.setfLastVoertuig(v);
    EXPECT_TRUE(v == b.getfLastVoertuig());
}

TEST_F(BaanTest, Baan_asignZoneLimit_postconditionNormal){

    Baan c = Baan();

    c.setLengte(100);
    c.setNaam("A1");

    Verkeersteken* v1 = new Verkeersteken();
    v1->setFPositie(1);
    v1->setFType("ZONE");
    v1->setFBaan("A1");
    v1->setFEndPositie(0);

    Verkeersteken* v2 = new Verkeersteken();
    v2->setFPositie(50);
    v2->setFType("ZONE");
    v2->setFBaan("A2");
    v2->setFEndPositie(0);

    c.addFVerkeersteken(v1);
    c.addFVerkeersteken(v2);

    c.assignZoneLimit();

    EXPECT_TRUE(50 == v1->getFEndPositie());
}

TEST_F(BaanTest, Baan_asignZoneLimit_postconditionLast){

    Baan c = Baan();

    c.setLengte(100);
    c.setNaam("A1");

    Verkeersteken* v1 = new Verkeersteken();
    v1->setFPositie(1);
    v1->setFType("ZONE");
    v1->setFBaan("A1");
    v1->setFEndPositie(0);

    Verkeersteken* v2 = new Verkeersteken();
    v2->setFPositie(50);
    v2->setFType("ZONE");
    v2->setFBaan("A2");
    v2->setFEndPositie(0);

    c.addFVerkeersteken(v1);
    c.addFVerkeersteken(v2);

    c.assignZoneLimit();

    EXPECT_TRUE(100 == v2->getFEndPositie());
}

TEST_F(BaanTest, Baan_asignZoneLimit_postconditionNegative){

    Baan c = Baan();

    c.setLengte(100);
    c.setNaam("A1");

    Verkeersteken* v1 = new Verkeersteken();
    v1->setFPositie(1);
    v1->setFType("ZONE");
    v1->setFBaan("A1");
    v1->setFEndPositie(0);

    Verkeersteken* v2 = new Verkeersteken();
    v2->setFPositie(50);
    v2->setFType("ZONE");
    v2->setFBaan("A2");
    v2->setFEndPositie(0);

    c.addFVerkeersteken(v1);
    c.addFVerkeersteken(v2);

    v2->setFPositie(0);

    EXPECT_DEATH(c.assignZoneLimit(),"");
}

TEST_F(BaanTest, Baan_asignZoneLimit_postconditionNegative2){

    Baan c = Baan();

    c.setLengte(100);
    c.setNaam("A1");

    Verkeersteken* v1 = new Verkeersteken();
    v1->setFPositie(1);
    v1->setFType("ZONE");
    v1->setFBaan("A1");
    v1->setFEndPositie(0);

    Verkeersteken* v2 = new Verkeersteken();
    v2->setFPositie(50);
    v2->setFType("ZONE");
    v2->setFBaan("A2");
    v2->setFEndPositie(0);

    c.addFVerkeersteken(v1);
    c.addFVerkeersteken(v2);

    v2->setFPositie(101);

    EXPECT_DEATH(c.assignZoneLimit(),"");
}
