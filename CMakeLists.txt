cmake_minimum_required(VERSION 3.13)
project(grobner-basis)

set(CMAKE_CXX_STANDARD 17)
include_directories("/Users/niazhabibulin/forStudy/boost_1_70_0")
include_directories("/Users/vlada/grobnerb_basis/boost_1_70_0/boost_1_70_0")

add_executable(grobner-basis main.cpp tests.cpp)