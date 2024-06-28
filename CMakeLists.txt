cmake_minimum_required(VERSION 3.16)
project(dev-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wpedantic")
SET(CMAKE_BUILD_TYPE Debug)

option(TEST "Enable testing" OFF)

include_directories(
  impl/include
)

if (TEST)
  MESSAGE("Building with tests")
  enable_testing()
  SET(CMAKE_BUILD_TYPE Debug)
  SET(CMAKE_CXX_FLAGS "-g -O3 --coverage -fprofile-arcs -ftest-coverage")
  SET(CMAKE_C_FLAGS "-g -O3 --coverage -fprofile-arcs -ftest-coverage")
endif()

add_subdirectory(impl)