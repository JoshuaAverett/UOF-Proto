# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice


cmake_minimum_required(VERSION 2.8)
project(UseOfForce)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
# set(CMAKE_BUILD_TYPE Release)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(third-party)
add_subdirectory(library)
add_subdirectory(client)
add_subdirectory(unit-tests)
add_subdirectory(extended-tests)
