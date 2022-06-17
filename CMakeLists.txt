cmake_minimum_required(VERSION 3.0.0)
project(GDPack VERSION 0.1.0)

file (GLOB_RECURSE SOURCES
        src/*.cpp
)

file (GLOB_RECURSE HEADERS
        src/*.h
        src/*.hpp
)

add_executable(GDPack ${SOURCES})