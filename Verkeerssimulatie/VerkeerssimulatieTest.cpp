//============================================================================
// Name        : Verkeerssimulatie.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

#include "System.h"
#include "XmlParser.h"

class VerkeerssimulatieTest: public ::testing::Test {
protected:
    friend class System;
    friend class XmlParser;

/**
virtual void SetUp() will be called before each test is run.  You
should define it if you need to initialize the variables.
Otherwise, this can be skipped.
*/
    virtual void SetUp() {
    }

/**
virtual void TearDown() will be called after each test is run.
You should define it if there is cleanup work to do.  Otherwise,
you don't have to provide it.
*/
    virtual void TearDown() {
    }

/**
Declares the variables your tests want to use.
*/

};

/**
Tests the default constructor.
*/

/// (class, name)
TEST_F(VerkeerssimulatieTest, DefaultConstructor) {

    XmlParser parser = XmlParser("Wegen_en_voertuigen.xml");

    EXPECT_TRUE(parser.properlyInitialized());
    // verify post-condition
}