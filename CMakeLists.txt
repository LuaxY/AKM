cmake_minimum_required(VERSION 2.8)

project (AKM)

IF(WIN32)
    set(BOOST_ROOT C:/lib/boost_1_55_0)
ENDIF(WIN32)

find_package(Boost)

add_subdirectory(src)