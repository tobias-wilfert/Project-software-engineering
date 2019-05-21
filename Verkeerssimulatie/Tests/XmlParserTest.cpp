//============================================================================
// Name        : XmlParserTest.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
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


/// ------ Check Parser Rigorously ------

/// ------ Old ------
// Can't work with non existing file
TEST_F(XmlParserTest, ConstructorWithNoneFile) {
    EXPECT_DEATH(XmlParser parser(""),"");
}

// Can't work with non XML File
TEST_F(XmlParserTest, ConstructorWithNonXMLFile) {
    EXPECT_DEATH(XmlParser parser("File.txt"),"");
}



/// ------ New ------
TEST_F(XmlParserTest,ParseEmpty){
    EXPECT_DEATH(XmlParser parser("Parser/Empty.xml"),"");
}

TEST_F(XmlParserTest,ParseEmptyRoot){
    EXPECT_DEATH(XmlParser parser("Parser/EmptyRoot.xml"),"");
}

TEST_F(XmlParserTest,BaanLengteFormat){

    // Redirect the cerr stream to a file indorder to compare it

    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanLengteFormat.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanLengteFormat.txt","Parser/XmlParserTest.txt"));
}


TEST_F(XmlParserTest,BaanLengteNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanLengteNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanLengteNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,BaanMurphy){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanMurphy.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanMurphy.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,BaanNaamNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanNaamNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanNaamNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,BaanSnelheidslimietFormat){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanSnelheidslimietFormat.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanSnelheidslimietFormat.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,BaanSnelheidslimietNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanSnelheidslimietNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanSnelheidslimietNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,BaanRijstrokenNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanRijstrokenNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanRijstrokenNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,BaanRijstrokenFormat){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanRijstrokenFormat.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanRijstrokenFormat.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,BaanRijstrokenFormatMin){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanRijstrokenFormatMin.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanRijstrokenFormatMin.txt","Parser/XmlParserTest.txt"));
}


TEST_F(XmlParserTest,BaanVerbindingNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/BaanVerbindingNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/BaanVerbindingNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigBaanNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigBaanNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigBaanNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigMurphy){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigMurphy.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigMurphy.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigNummerplaatNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigNummerplaatNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigNummerplaatNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigPositieFormat){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigPositieFormat.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigPositieFormat.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigPositieFormatMin){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigPositieFormatMin.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigPositieFormatMin.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigPositieNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigPositieNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigPositieNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigSnelheidFormat){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigSnelheidFormat.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigSnelheidFormat.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigSnelheidFormatMin){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigSnelheidFormatMin.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigSnelheidFormatMin.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigSnelheidNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigSnelheidNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigSnelheidNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigTypeNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigTypeNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigTypeNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VoertuigTypeUnkown){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VoertuigTypeUnkown.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VoertuigTypeUnkown.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenBaanFormat){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenBaanFormat.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenBaanFormat.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenBaanNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenBaanNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenBaanNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenMurphy){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenMurphy.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenMurphy.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenPositieFormat){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenPositieFormat.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenPositieFormat.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenPositieFormatMin){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenPositieFormatMin.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenPositieFormatMin.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenPositieNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenPositieNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenPositieNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenSnelheidslimietFormat){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenSnelheidslimietFormat.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenSnelheidslimietFormat.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenSnelheidslimietFormatMin){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenSnelheidslimietFormatMin.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenSnelheidslimietFormatMin.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenSnelheidslimietNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenSnelheidslimietNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenSnelheidslimietNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenTypeFormat){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenTypeFormat.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenTypeFormat.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,VerkeerstekenTypeNULL){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/VerkeerstekenTypeNULL.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/VerkeerstekenTypeNULL.txt","Parser/XmlParserTest.txt"));
}

TEST_F(XmlParserTest,AllMurphy){

    // Redirect the cerr stream to a file indorder to compare it
    std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
    std::ofstream out("Parser/XmlParserTest.txt");
    std::cerr.rdbuf(out.rdbuf());

    XmlParser parser("Parser/AllMurphy.xml");
    std::cerr.rdbuf(cerrbuf); //reset to standard output again
    EXPECT_TRUE(parser.compareFiles("Parser/AllMurphy.txt","Parser/XmlParserTest.txt"));
}
