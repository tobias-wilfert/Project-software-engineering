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

class TicTactToeTest: public ::testing::Test {
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

// Tests the default constructor.
TEST_F(TicTactToeTest, DefaultConstructor) {

    XmlParser parser("Wegen_en_voertuigen.xml");

    EXPECT_TRUE((parser.properlyInitialized()));
    EXPECT_TRUE((parser.getBanen()->size() > 0));

    EXPECT_TRUE((parser.getVoertuigen()->size() > 0));
    EXPECT_TRUE((parser.getWegenNetwerk()->size() >= 0));
}

// Tests the default constructor.
TEST_F(TicTactToeTest, SpecialConstructor) {

    XmlParser parser("Wegennetwerk.xml");
    EXPECT_TRUE((parser.properlyInitialized()));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

