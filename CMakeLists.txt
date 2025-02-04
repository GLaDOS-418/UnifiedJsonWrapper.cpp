cmake_minimum_required(VERSION 3.23)

project(UnifiedJsonWrapper CXX)

#
# cpp standard
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#
# Compiler flags
#
set(CMAKE_COMPILE_WARNING_AS_ERROR True)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")

#
# Build options
#
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message("\"${CMAKE_BUILD_TYPE}\" type build.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(cmake/compiler_options.cmake)
include(cmake/static_analyzers.cmake)

#
# add library
#
add_subdirectory(Wrappers)

#
# add tests
#
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(Tests)
endif()
