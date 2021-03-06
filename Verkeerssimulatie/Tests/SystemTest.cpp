//============================================================================
// Name        : SystemTest.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "../System.h"
#include "../XmlParser.h"

class SystemTest: public ::testing::Test {
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



/////////////////////////////////Begin System Tests////////////////////////////////////////////////////

TEST_F(SystemTest, organizeVehicles){
    XmlParser parser3("Parser/SYSTEMorganizeVehiclesTest.xml");
    System s(parser3.getBanen(), parser3.getWegenNetwerk(), parser3.getVoertuigen());
    Voertuig *nullpointer = NULL;  //nullpointer van Object Voertuig
    EXPECT_EQ(s.getVoertuigen()->at(0)->getNextVoertuig(), nullpointer);
    EXPECT_EQ(s.getVoertuigen()->at(1)->getNextVoertuig(), nullpointer);
    EXPECT_EQ(s.getVoertuigen()->at(2)->getNextVoertuig(), nullpointer);
    EXPECT_EQ(s.getVoertuigen()->at(3)->getNextVoertuig(), nullpointer);

    s.organizeVehicles();


    EXPECT_EQ(s.getVoertuigen()->at(0)->getNextVoertuig()->getNummerPlaat(), "651BUFF");
    EXPECT_EQ(s.getVoertuigen()->at(1)->getNextVoertuig()->getNummerPlaat(), "1THK180");
    EXPECT_EQ(s.getVoertuigen()->at(2)->getNextVoertuig()->getNummerPlaat(), "651BUFFF");
    EXPECT_EQ(s.getVoertuigen()->at(3)->getNextVoertuig(), nullpointer);

    EXPECT_EQ(s.getVoertuigen()->at(0)->getPositie(), 10);
    EXPECT_EQ(s.getVoertuigen()->at(1)->getPositie(), 0);
    EXPECT_EQ(s.getVoertuigen()->at(2)->getPositie(), 15);
    EXPECT_EQ(s.getVoertuigen()->at(3)->getPositie(), 1990);
}


TEST_F(SystemTest, initializeVehicleBaanObject){
    XmlParser parser4("Parser/SYSTEMinitializeVehicleBaanObjectTest.xml");
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

XmlParser parser5("Parser/SYSTEMinitializeBaanVerbindingObjectsTest.xml");
System s = System(parser5.getBanen(), parser5.getWegenNetwerk(), parser5.getVoertuigen());

TEST_F(SystemTest, initializeBaanVerbindingObjects){
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

XmlParser parser6("Parser/SYSTEMfilterVehiclesTest.xml");
System s1(parser6.getBanen(), parser6.getWegenNetwerk(), parser6.getVoertuigen());
TEST_F(SystemTest, filterVehicles){
    unsigned int x = 4;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);
    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    x = 3;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);
    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    x = 2;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);
    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    x = 1;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);

    s1.getVoertuigen()->at(0)->setDeleteObject(true);

    s1.filterVehicles();
    x = 0;
    EXPECT_EQ(s1.getVoertuigen()->size(), x);

}

XmlParser parser7("Parser/SYSTEMgetBanenEnWegenNetwerkTest.xml");
System s2(parser7.getBanen(), parser7.getWegenNetwerk(), parser7.getVoertuigen());
TEST_F(SystemTest, getBanen){
    unsigned int x = 4;
    EXPECT_EQ(s2.getBanen()->size(), x);
    EXPECT_EQ(s2.getBanen()->at(0)->getNaam(), "E10");
    EXPECT_EQ(s2.getBanen()->at(1)->getNaam(), "E20");
    EXPECT_EQ(s2.getBanen()->at(2)->getNaam(), "E30");
    EXPECT_EQ(s2.getBanen()->at(3)->getNaam(), "E40");
}

TEST_F(SystemTest, getWegenNetwerk){
    unsigned int x = 5;
    EXPECT_EQ(s2.getWegenNetwerk()->size(), x);
    EXPECT_EQ(s2.getWegenNetwerk()->at(0)->getNaam(), "E60");
    EXPECT_EQ(s2.getWegenNetwerk()->at(1)->getNaam(), "E70");
    EXPECT_EQ(s2.getWegenNetwerk()->at(2)->getNaam(), "E80");
    EXPECT_EQ(s2.getWegenNetwerk()->at(3)->getNaam(), "E90");
    EXPECT_EQ(s2.getWegenNetwerk()->at(4)->getNaam(), "E100");
}

XmlParser parser8("Parser/SYSTEMsimulateTest.xml");
System s3(parser8.getBanen(), parser8.getWegenNetwerk(), parser8.getVoertuigen());



TEST_F(SystemTest, automaticSimulation){
    unsigned int x = 6;
    EXPECT_EQ(s3.getVoertuigen()->size(), x);

    // Write the output to a file to comapare them later
    // Redirect streams

    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::ofstream out("dummyTest.txt");
    std::cout.rdbuf(out.rdbuf());

    s3.automaticSimulation();


    std::cout.rdbuf(coutbuf); //reset to standard output again

    x = 0;
    EXPECT_EQ(s3.getVoertuigen()->size(), x);
}


TEST_F(SystemTest, automaticSimulation_precondition){

    std::vector<Baan*> b;
    std::vector<Baan*> w;
    std::vector<Voertuig*> v;

    Baan* b1 = new Baan;
    b1->setLengte(100);
    b.push_back(b1);

    System s0 = System(&b,&w,&v);

    EXPECT_DEATH(s0.automaticSimulation("complex","dummyTest",75),"");
}

TEST_F(SystemTest, automaticSimulation_precondition1){

    std::vector<Baan*> b;
    std::vector<Baan*> w;
    std::vector<Voertuig*> v;

    Baan* b1 = new Baan;
    b1->setLengte(100);
    b.push_back(b1);

    System s0 = System(&b,&w,&v);

    EXPECT_DEATH(s0.automaticSimulation("complex","",25),"");
}

TEST_F(SystemTest, automaticSimulation_precondition2){

    std::vector<Baan*> b;
    std::vector<Baan*> w;
    std::vector<Voertuig*> v;

    Baan* b1 = new Baan;
    b1->setLengte(100);
    b.push_back(b1);

    System s0 = System(&b,&w,&v);

    EXPECT_DEATH(s0.automaticSimulation("complex","dummyTest",25,-1),"");
}

TEST_F(SystemTest, grafischeImpressie_precondition){

    std::vector<Baan*> b;
    std::vector<Baan*> w;
    std::vector<Voertuig*> v;

    Baan* b1 = new Baan;
    b1->setLengte(100);
    b.push_back(b1);

    System s0 = System(&b,&w,&v);

    EXPECT_DEATH(s0.grafischeImpressie("dummyTest",75,0),"");
}

TEST_F(SystemTest, grafischeImpressie_precondition1){

    std::vector<Baan*> b;
    std::vector<Baan*> w;
    std::vector<Voertuig*> v;

    Baan* b1 = new Baan;
    b1->setLengte(100);
    b.push_back(b1);

    System s0 = System(&b,&w,&v);

    EXPECT_DEATH(s0.grafischeImpressie("",25,0),"");
}

TEST_F(SystemTest, grafischeImpressie_precondition2){

    std::vector<Baan*> b;
    std::vector<Baan*> w;
    std::vector<Voertuig*> v;

    Baan* b1 = new Baan;
    b1->setLengte(100);
    b.push_back(b1);

    System s0 = System(&b,&w,&v);

    EXPECT_DEATH(s0.grafischeImpressie("dummyTest",25,-1),"");
}

TEST_F(SystemTest,initializeBaanVerbindingObjects_postcondition){
    std::vector<Baan*> b;
    std::vector<Baan*> w;
    std::vector<Voertuig*> v;

    Baan* b1 = new Baan;
    b1->setLengte(100);
    b1->setNaam("A12");

    Baan* b2  = new Baan;
    b2->setLengte(200);
    b2->setNaam("A10");
    b2->setVerbinding("A12");

    b.push_back(b1);
    w.push_back(b2);

    System s0 = System(&b,&w,&v);

    s0.initializeBaanVerbindingObjects();
}

TEST_F(SystemTest,initializeBaanVerbindingObjects_postconditionNegative){
    std::vector<Baan*> b;
    std::vector<Baan*> w;
    std::vector<Voertuig*> v;

    Baan* b1 = new Baan;
    b1->setLengte(100);
    b1->setNaam("A12");

    Baan* b2  = new Baan;
    b2->setLengte(200);
    b2->setNaam("A10");
    b2->setVerbinding("A13");

    b.push_back(b1);
    w.push_back(b2);

    System s0 = System(&b,&w,&v);

    EXPECT_DEATH(s0.initializeBaanVerbindingObjects(),"");
}

TEST_F(SystemTest,initializeBaanVerbindingObjects_organizeVehicles){
    std::vector<Baan*> b;
    std::vector<Baan*> w;
    std::vector<Voertuig*> v;

    Baan* b1 = new Baan;
    b1->setLengte(1000);
    b1->setNaam("A12");

    b.push_back(b1);

    Voertuig* v1 = new Voertuig();
    Voertuig* v2 = new Voertuig();
    Voertuig* v3 = new Voertuig();

    v1->setPositie(50);
    v2->setPositie(100);
    v3->setPositie(500);

    v.push_back(v3);
    v.push_back(v2);
    v.push_back(v1);

    System s0 = System(&b,&w,&v);

    s0.organizeVehicles();

    EXPECT_TRUE(v1->getNextVoertuig() == v2);
}

TEST_F(SystemTest, outputVerkeersteken) {

    std::vector<Baan *> b;
    std::vector<Baan *> w;
    std::vector<Voertuig *> v;

    Baan *b1 = new Baan;
    b1->setLengte(100);

    System s0 = System(&b, &w, &v);

    EXPECT_DEATH(s0.outputVerkeersteken(b1, 75), "");
}

/////////////////////////////////Test output of entire sysytem////////////////////////////////////////////////////

TEST_F(SystemTest, entireSystem_BusTest){
    XmlParser parser("SystemOutput/BusTest.xml");
    System systemTest(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Redirect streams
    std::ofstream out("dummyTest.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();//save old buf
    std::cout.rdbuf(out.rdbuf());

    systemTest.automaticSimulation("simpele");

    std::cout.rdbuf(coutbuf);
    EXPECT_TRUE(systemTest.compareFiles("dummyTest.txt","SystemOutput/BusTest.txt"));
}

TEST_F(SystemTest, entireSystem_Holiday){
    XmlParser parser("SystemOutput/Holiday.xml");
    System systemTest(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Redirect streams
    std::ofstream out("dummyTest.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();//save old buf
    std::cout.rdbuf(out.rdbuf());

    systemTest.automaticSimulation("simpele");

    std::cout.rdbuf(coutbuf);
    EXPECT_TRUE(systemTest.compareFiles("dummyTest.txt","SystemOutput/Holiday.txt"));
}

TEST_F(SystemTest, entireSystem_MondayMorning){
    XmlParser parser("SystemOutput/MondayMorning.xml");
    System systemTest(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Redirect streams
    std::ofstream out("dummyTest.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();//save old buf
    std::cout.rdbuf(out.rdbuf());

    systemTest.automaticSimulation("simpele");

    std::cout.rdbuf(coutbuf);
    EXPECT_TRUE(systemTest.compareFiles("dummyTest.txt","SystemOutput/MondayMorning.txt"));
}

TEST_F(SystemTest, entireSystem_RoadWork){
    XmlParser parser("SystemOutput/RoadWork.xml");
    System systemTest(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Redirect streams
    std::ofstream out("dummyTest.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();//save old buf
    std::cout.rdbuf(out.rdbuf());

    systemTest.automaticSimulation("simpele");

    std::cout.rdbuf(coutbuf);
    EXPECT_TRUE(systemTest.compareFiles("dummyTest.txt","SystemOutput/RoadWork.txt"));
}

TEST_F(SystemTest, entireSystem_RushHour){
    XmlParser parser("SystemOutput/RushHour.xml");
    System systemTest(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Redirect streams
    std::ofstream out("dummyTest.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();//save old buf
    std::cout.rdbuf(out.rdbuf());

    systemTest.automaticSimulation("simpele");

    std::cout.rdbuf(coutbuf);
    EXPECT_TRUE(systemTest.compareFiles("dummyTest.txt","SystemOutput/RushHour.txt"));
}

TEST_F(SystemTest, entireSystem_1stTest){
    XmlParser parser("SystemOutput/1stTest.xml");
    System systemTest(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Redirect streams
    std::ofstream out("dummyTest.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();//save old buf
    std::cout.rdbuf(out.rdbuf());

    systemTest.automaticSimulation("simpele");

    std::cout.rdbuf(coutbuf);
    EXPECT_TRUE(systemTest.compareFiles("dummyTest.txt","SystemOutput/1stTest.txt"));
}

TEST_F(SystemTest, entireSystem_2ndTest){
    XmlParser parser("SystemOutput/2ndTest.xml");
    System systemTest(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Redirect streams
    std::ofstream out("dummyTest.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();//save old buf
    std::cout.rdbuf(out.rdbuf());

    systemTest.automaticSimulation("simpele");

    std::cout.rdbuf(coutbuf);
    EXPECT_TRUE(systemTest.compareFiles("dummyTest.txt","SystemOutput/2ndTest.txt"));
}

TEST_F(SystemTest, entireSystem_BusInc){
    XmlParser parser("SystemOutput/BusInc.xml");
    System systemTest(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Redirect streams
    std::ofstream out("dummyTest.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();//save old buf
    std::cout.rdbuf(out.rdbuf());

    systemTest.automaticSimulation("simpele");

    std::cout.rdbuf(coutbuf);
    EXPECT_TRUE(systemTest.compareFiles("dummyTest.txt","SystemOutput/BusInc.txt"));
}

TEST_F(SystemTest, entireSystem_MotorFiestInc){
    XmlParser parser("SystemOutput/MotorFiestInc.xml");
    System systemTest(parser.getBanen(), parser.getWegenNetwerk(), parser.getVoertuigen());

    // Redirect streams
    std::ofstream out("dummyTest.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();//save old buf
    std::cout.rdbuf(out.rdbuf());

    systemTest.automaticSimulation("simpele");

    std::cout.rdbuf(coutbuf);
    EXPECT_TRUE(systemTest.compareFiles("dummyTest.txt","SystemOutput/MotorFiestInc.txt"));
}