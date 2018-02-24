cmake_minimum_required(VERSION 3.5)
project(hw4)

set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11")
file(GLOB SRC ./*.cpp)
file(GLOB INCL ./*.h)

add_executable(hw4 ${SRC} ${INCL})
