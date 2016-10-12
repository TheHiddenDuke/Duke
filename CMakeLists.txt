cmake_minimum_required(VERSION 3.6)
project(ringBuffer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp ringBuffer.cpp ringBuffer.h)
add_executable(ringBuffer ${SOURCE_FILES})