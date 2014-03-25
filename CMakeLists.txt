cmake_minimum_required(VERSION 2.8)

project (AKM)

if(WIN32)
    set(BOOST_ROOT C:/lib/boost_1_55_0)
    find_package(Boost)
endif(WIN32)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
    find_package(Boost COMPONENTS system thread REQUIRED)
endif()


add_subdirectory(src)