//============================================================================
// Name        : VerkeerstekenTest.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "../Baan.h"
#include "../Verkeersteken.h"

class VerkeerstekenTest: public ::testing::Test {
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
Verkeersteken v = Verkeersteken();

TEST_F(VerkeerstekenTest, setFBaan_precondition ){

    v.setFBaan("E19");
    EXPECT_TRUE(v.getFBaan() == "E19");
}

TEST_F(VerkeerstekenTest, setFType_precondition_1){
    EXPECT_DEATH(v.setFType("car"),"");
}

TEST_F(VerkeerstekenTest, setFType_precondition_2){
    EXPECT_DEATH(v.setFType("boat"),"");
}

TEST_F(VerkeerstekenTest, setFType_precondition_3){
    EXPECT_DEATH(v.setFType("zoo"),"");
}

TEST_F(VerkeerstekenTest, setFType_precondition_4){
    EXPECT_DEATH(v.setFType("AUTO"),"");
}

TEST_F(VerkeerstekenTest, setFType_precondition_5){
    v.setFType("BUSHALTE");
}

TEST_F(VerkeerstekenTest, setFType_precondition_6){
    v.setFType("ZONE");
}

TEST_F(VerkeerstekenTest, setFType_precondition_7){
    v.setFType("VERKEERSLICHT");
}

TEST_F(VerkeerstekenTest, setFType_postcondition){
    v.setFType("VERKEERSLICHT");
    EXPECT_TRUE(v.getFType() == "VERKEERSLICHT" );
}

TEST_F(VerkeerstekenTest, setFPositie_postcondition){
    v.setFPositie(10);
    EXPECT_TRUE(v.getFPositie() == 10);
}

TEST_F(VerkeerstekenTest, setFSnelheidslimiet_postcondition){
    v.setFSnelheidslimiet(100);
    EXPECT_TRUE(v.getFSnelheidslimiet() == 100);
}

TEST_F(VerkeerstekenTest, setFEndPositie_postcondition){
    v.setFEndPositie(1000);
    EXPECT_TRUE(v.getFEndPositie() == 1000);
}
