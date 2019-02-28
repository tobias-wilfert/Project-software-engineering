#include <iostream>

#include "XmlParser.h"

int main() {

    const char* fileName =  "Wegennetwerk.xml";

    //vector<Weeg*> wegen;
    //vector<Auto*> autos;
    //vector<WegenNetwerk*> wegenNetwerken;

    XmlParser parser = XmlParser(fileName);
    //vector<Weeg*> wegen = parser.wegen()

    std::cout << "Hello, World!" << std::endl;


    //XmlParser* parserr = new XmlParser(file);
    return 0;


}

/*
 *  sim simulatie
    XmlParser obj(file simulatie) ->
parsen van xml file
    DOEL:
    bepaal wat voor input bestand het bestand is{
        vector<string type> types;
        Type overloop elk root element{
            if root == voertuig{
                types.pushback(voertuigen)
                }
            if root ==  Baan{
                for elk baan element{
                    if verbinding{
                        types.pushack(WegenNetwerkBaan)
                    }
                    else{
                        types.pushback(Baan)
                    }


                }
            }
        }
        //wij hebben nu elke baan overlopen dus nu zijn we zeker dat het geen wegennetwerk is
        if atleast 1 WegenNetwerkBaan:
};





for every Root element{
    if voertuig{
        bool = makeObj;
        for every elemnt{
            if type
            if nummerplaat
            if baan
            if positie
            if snelheid
        }

    }
    if baan{
        bool wegennetwerk=false;
        for every baan element{
                if element == verbinding{
                    wegennetwerk == true
                }
        }


    }
}


    //baan
        verbinding

vliegveld
    //baan
        verbinding

        */