cmake_minimum_required(VERSION 3.11)
project(gdpack VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        URL https://github.com/fmtlib/fmt/releases/download/8.1.1/fmt-8.1.1.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(fmt json)

file(GLOB_RECURSE SOURCES
        src/*.cpp
)

file(GLOB_RECURSE HEADERS
        src/*.h
        src/*.hpp
)

add_executable(gdpack ${SOURCES})
target_precompile_headers(gdpack PUBLIC ${HEADERS})
target_compile_definitions(gdpack PRIVATE)

target_include_directories(gdpack PRIVATE include)
target_link_libraries(gdpack PRIVATE nlohmann_json::nlohmann_json fmt::fmt)