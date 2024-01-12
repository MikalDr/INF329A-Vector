cmake_minimum_required(VERSION 3.26)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled1 main.cpp
        basic/basic_operators.cpp
        basic/basic_operators.h
        list.h
        transformations/transformations.h
        folds/folds.h
        searching/search.h
        sublist/sublist.h
        zipping/zip.h
        special/special.h
        unityped.h)
