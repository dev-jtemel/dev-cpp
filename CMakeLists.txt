cmake_minimum_required(VERSION 3.16)
project(dev-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wpedantic")
SET(CMAKE_BUILD_TYPE Debug)

include_directories(
  impl/include
)

add_subdirectory(impl)
