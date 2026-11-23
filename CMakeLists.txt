cmake_minimum_required(VERSION 3.21)
project(LinearLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(LinearSolverLib STATIC
    src/LinearSystem.cpp
)
target_include_directories(LinearSolverLib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(LinearDemo
    demo/main.cpp
)
target_link_libraries(LinearDemo
    PRIVATE LinearSolverLib
)

add_executable(AntipatternDemo
    antipattern/main.cpp
)

find_package(GTest CONFIG REQUIRED)
enable_testing()

add_executable(LinearTests
    tests/LinearTests.cpp
)
target_link_libraries(LinearTests
    PRIVATE
    LinearSolverLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(LinearTests)