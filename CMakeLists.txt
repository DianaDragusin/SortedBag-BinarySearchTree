cmake_minimum_required(VERSION 3.21)
project(SortedBag)

set(CMAKE_CXX_STANDARD 14)


add_executable(SortedBag
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedBag.cpp
        SortedBag.h
        SortedBagIterator.cpp
        SortedBagIterator.h)
