//============================================================================
// Name        : FileCompareTest.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "../System.h"
#include "../XmlParser.h"

class FileCompareTest: public ::testing::Test {
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

// Make an instance of parse so we can use the compare on it.
XmlParser parserForCompare = XmlParser("Parser/Working.xml");
System systemForCompare = System(parserForCompare.getBanen(),parserForCompare.getWegenNetwerk(),
        parserForCompare.getVoertuigen());

// Check that eveything is setup correctly
TEST_F(FileCompareTest, properlyInitialized) {
    EXPECT_TRUE(parserForCompare.properlyInitialized());
    EXPECT_TRUE(systemForCompare.properlyInitialized());
}

TEST_F(FileCompareTest, emptyAndEmptySame) {
    EXPECT_TRUE(parserForCompare.compareFiles("FileCompare/Empty1.txt","FileCompare/Empty1.txt"));
    EXPECT_TRUE(parserForCompare.compareFiles("FileCompare/Empty2.txt","FileCompare/Empty2.txt"));


    EXPECT_TRUE(systemForCompare.compareFiles("FileCompare/Empty1.txt","FileCompare/Empty1.txt"));
    EXPECT_TRUE(systemForCompare.compareFiles("FileCompare/Empty2.txt","FileCompare/Empty2.txt"));
}

TEST_F(FileCompareTest, emptyAndEmptyDifferent) {
    EXPECT_TRUE(parserForCompare.compareFiles("FileCompare/Empty2.txt","FileCompare/Empty1.txt"));
    EXPECT_TRUE(parserForCompare.compareFiles("FileCompare/Empty1.txt","FileCompare/Empty2.txt"));

    EXPECT_TRUE(systemForCompare.compareFiles("FileCompare/Empty1.txt","FileCompare/Empty2.txt"));
    EXPECT_TRUE(systemForCompare.compareFiles("FileCompare/Empty2.txt","FileCompare/Empty1.txt"));
}

TEST_F(FileCompareTest, existingAndNoneExisting) {
    EXPECT_FALSE(parserForCompare.compareFiles("FileCompare/Empty1.txt","None.txt"));

    EXPECT_FALSE(systemForCompare.compareFiles("FileCompare/Empty1.txt","None.txt"));
}

TEST_F(FileCompareTest, noneexistingAndNoneExisting) {
    EXPECT_FALSE(parserForCompare.compareFiles("None.txt","None.txt"));

    EXPECT_FALSE(systemForCompare.compareFiles("None.txt","None.txt"));
}

TEST_F(FileCompareTest, Equal) {
    EXPECT_TRUE(parserForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/Whitman2.txt"));

    EXPECT_TRUE(systemForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/Whitman2.txt"));
}

TEST_F(FileCompareTest, Identical) {
    EXPECT_TRUE(parserForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/Whitman.txt"));

    EXPECT_TRUE(systemForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/Whitman.txt"));
}

TEST_F(FileCompareTest, Shorter) {
    EXPECT_FALSE(parserForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/WhitmanShort.txt"));

    EXPECT_FALSE(systemForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/WhitmanShort.txt"));
}

TEST_F(FileCompareTest, Longer) {
    EXPECT_FALSE(parserForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/WhitmanLong.txt"));

    EXPECT_FALSE(systemForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/WhitmanLong.txt"));
}

TEST_F(FileCompareTest, Different) {
    EXPECT_FALSE(parserForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/TwoCities.txt"));

    EXPECT_FALSE(systemForCompare.compareFiles("FileCompare/Whitman.txt","FileCompare/TwoCities.txt"));
}