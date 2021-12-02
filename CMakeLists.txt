cmake_minimum_required(VERSION 3.0.0)
project(DataSructuresHW2 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_MAKE_PROGRAM C:/Program Files/CMake/bin/cmake.exe FORCE )

include(CTest)
enable_testing()
set(CMAKE_BUILD_TYPE Debug)
set(FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")
set(CMAKE_CPP_FLAGS ${FLAGS_DEBUG})
set(CPP_FILES 
./DataStructures/Player.cpp
./DataStructures/Level.cpp
./DataStructures/Group.cpp
./DataStructures/Game.cpp
./DataStructures/library1.cpp
./DataStructures/main1.cpp
)
add_executable(DataSructuresHW2 ${CPP_FILES})

