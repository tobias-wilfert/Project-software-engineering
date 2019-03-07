#include <iostream>
#include "System.h"
#include "XmlParser.h"

int main() {

    const char* fileName =  "Wegennetwerk.xml";

    XmlParser parser = XmlParser(fileName);

    System system = System();

    std::cout << "The program executed till here without crashing." << std::endl;
    return 0;
}
