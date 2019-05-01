cmake_minimum_required(VERSION 3.6)
project(Verkeerssimulatie)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES main.cpp Parser/tinystr.cpp Parser/tinystr.h Parser/tinyxml.cpp Parser/tinyxml.h Parser/tinyxmlerror.cpp Parser/tinyxmlparser.cpp XmlParser.cpp XmlParser.h Voertuig.cpp Voertuig.h Baan.cpp Baan.h System.cpp System.h DesignByContract.h Verkeersteken.cpp Verkeersteken.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        Tests/VerkeerssimulatieTest.cpp
        Tests/XmlParserTest.cpp
        Tests/VoertuigTest.cpp
        Tests/SystemTest.cpp
        Tests/BaanTest.cpp
        Parser/tinystr.cpp
        Parser/tinystr.h
        Parser/tinyxml.cpp
        Parser/tinyxml.h
        Parser/tinyxmlerror.cpp
        Parser/tinyxmlparser.cpp
        DesignByContract.h
        XmlParser.cpp
        XmlParser.h
        Voertuig.cpp
        Voertuig.h
        Baan.cpp
        Baan.h
        System.cpp
        System.h
        Verkeersteken.cpp
        Verkeersteken.h Tests/VerkeerstekenTest.cpp)

# Create RELEASE target
add_executable(Verkeerssimulatie ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(Verkeerssimulatie_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(Verkeerssimulatie_debug gtest)
