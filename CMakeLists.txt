cmake_minimum_required(VERSION 3.6)
project(CG2016_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    color.cpp
    color.hpp
    coordinates.cpp
    coordinates.hpp
    curve.cpp
    curve.hpp
    line.cpp
    line.hpp
    main.cpp
    matriz1x3.cpp
    matriz1x3.hpp
    matriz3x3.cpp
    matriz3x3.hpp
    object.cpp
    object.hpp
    operations.cpp
    point.cpp
    point.hpp
    polygon.cpp
    polygon.hpp
    simple.glade
    transformations.cpp
    ui.cpp
    ui.hpp
    window.cpp
    window.hpp
    wireframe.cpp
    wireframe.hpp
    world.cpp
    world.hpp)

add_executable(CG2016_2 ${SOURCE_FILES})