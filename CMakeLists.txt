cmake_minimum_required(VERSION 3.10)

set(This Soundex)

project(${this} CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(test)

set(Headers
  Soundex.hpp
  CommandLineInterface.hpp
)

set(Sources
  Soundex.cpp
  CommandLineInterface.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_test(
  NAME ${This}
  COMMAND ${This}
)