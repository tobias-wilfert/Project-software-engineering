//============================================================================
// Name        : XmlParserTest.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 2.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "../System.h"
#include "../XmlParser.h"

class XmlParserTest: public ::testing::Test {
protected:
    friend class System;
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

};

/// Check Parser Parsing File

// Tests the default constructor.
TEST_F(XmlParserTest, DefaultConstructor) {

    XmlParser parser("Wegen_en_voertuigen.xml");

    EXPECT_TRUE((parser.properlyInitialized()));
    EXPECT_TRUE((parser.getBanen()->size() > 0));
    EXPECT_TRUE((parser.getVoertuigen()->size() > 0));
    EXPECT_TRUE((parser.getWegenNetwerk()->size() >= 0));
}

// Can't work with non existing file
TEST_F(XmlParserTest, ConstructorWithNoneFile) {
    EXPECT_DEATH(XmlParser parser(""),"");
    //EXPECT_EXIT(XmlParser parser(""), ::testing::ExitedWithCode(1), "");
}

// Can't work with non XML File
TEST_F(XmlParserTest, ConstructorWithNonXMLFile) {
    EXPECT_DEATH(XmlParser parser("File.txt"),"");
    //EXPECT_EXIT(XmlParser parser("File.xml"), ::testing::ExitedWithCode(1), "");
}

// Can't work with empty XML File
TEST_F(XmlParserTest, ConstructorWithEmptyXMLFile) {
    EXPECT_DEATH(XmlParser parser("Empty.xml"),"");
    //EXPECT_EXIT(XmlParser parser("Empty.xml"), ::testing::ExitedWithCode(1), "");
}

// Can't work with wrongly XML File
TEST_F(XmlParserTest, ConstructorWithWronglyXMLFile) {
    EXPECT_DEATH(XmlParser parser("Wrong.xml"),"");
    //EXPECT_EXIT(XmlParser parser("Wrong.xml"), ::testing::ExitedWithCode(1), "");
}

/// Check Help functions
