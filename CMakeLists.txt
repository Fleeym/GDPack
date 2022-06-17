cmake_minimum_required(VERSION 3.11)
project(GDPack VERSION 0.1.0)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

file (GLOB_RECURSE SOURCES
        src/*.cpp
)

file (GLOB_RECURSE HEADERS
        src/*.h
        src/*.hpp
)

add_executable(GDPack ${SOURCES})
target_include_directories(GDPack PRIVATE include)
target_link_libraries(GDPack PRIVATE nlohmann_json::nlohmann_json)