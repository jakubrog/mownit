cmake_minimum_required(VERSION 3.13)
project(test C)

set(CMAKE_C_STANDARD 11)

add_executable(test main.c)
set(CMAKE_CXX_STANDARD_REQUIRED YES)  ## this too

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(test GSL::gsl GSL::gslcblas) #needs to be add
