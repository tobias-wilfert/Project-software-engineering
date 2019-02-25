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
#set(RELEASE_SOURCE_FILES src/TicTacToe.cpp src/TicTacToeMain.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES main.cpp tinystr.cpp tinystr.h tinyxml.cpp tinyxml.h tinyxmlerror.cpp tinyxmlparser.cpp)

# Create RELEASE target
#add_executable(Verkeerssimulatie ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(Verkeerssimulatie_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(Verkeerssimulatie_debug gtest)
