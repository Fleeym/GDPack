cmake_minimum_required(VERSION 3.16)
project(gdpack VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

file(GLOB_RECURSE SOURCES
        src/*.cpp
)

file(GLOB_RECURSE HEADERS
        src/*.h
        src/*.hpp
)

add_subdirectory(include/fmt)
add_subdirectory(include/json)

add_executable(${PROJECT_NAME} ${SOURCES})
target_precompile_headers(${PROJECT_NAME} PUBLIC ${HEADERS})
target_compile_definitions(${PROJECT_NAME} PRIVATE)

target_include_directories(${PROJECT_NAME} PRIVATE include/fmt include/json)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json fmt::fmt)