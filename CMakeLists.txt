cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(mathexpr LANGUAGES CXX)

if (${CMAKE_HOST_WIN32})
    message(STATUS "Win32")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)    
endif()


add_library(mathexpr_lib SHARED mathexpr.cpp calculator.cpp parser.cpp)
target_include_directories(mathexpr_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(mathexpr_exe main.cpp)
target_link_libraries(mathexpr_exe PUBLIC mathexpr_lib)