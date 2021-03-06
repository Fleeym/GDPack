cmake_minimum_required(VERSION 3.11)
project(GDPack VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(fmt URL https://github.com/fmtlib/fmt/releases/download/8.1.1/fmt-8.1.1.zip)
FetchContent_MakeAvailable(fmt)

file (GLOB_RECURSE SOURCES
        src/*.cpp
)

file (GLOB_RECURSE HEADERS
        src/*.h
        src/*.hpp
)

add_executable(GDPack ${SOURCES})
target_precompile_headers(GDPack PUBLIC ${HEADERS})

target_include_directories(GDPack PRIVATE include)
target_link_libraries(GDPack PRIVATE nlohmann_json::nlohmann_json fmt::fmt)