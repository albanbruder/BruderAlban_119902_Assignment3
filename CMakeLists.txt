cmake_minimum_required(VERSION 2.8)
project(assignment3)

if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND UNIX))
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++14 -Wall")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
  set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
endif()

# Add externals
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_definitions(-DGLEW_STATIC)

# Use catch for testing
set(CATCH_DIRECTORY catch-2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${CATCH_DIRECTORY})

add_subdirectory(source)
