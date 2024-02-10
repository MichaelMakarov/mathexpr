cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(mathexpr LANGUAGES CXX)

add_library(mathexpr_lib mathexpr.cpp calculator.cpp parser.cpp)
target_include_directories(mathexpr_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(mathexpr_exe main.cpp)
target_link_libraries(mathexpr_exe PUBLIC mathexpr_lib)