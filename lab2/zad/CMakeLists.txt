cmake_minimum_required(VERSION 3.13)
project(zad C)

set(CMAKE_C_STANDARD 11)

add_executable(zad main.c)
set(CMAKE_CXX_STANDARD_REQUIRED YES)  ## this too

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(zad GSL::gsl GSL::gslcblas) #needs to be add
