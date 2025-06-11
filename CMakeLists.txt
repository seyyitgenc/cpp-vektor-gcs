cmake_minimum_required(VERSION 3.10)

# set the project name
project(flightpulsemonitor)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CLIENT_NAME "${PROJECT_NAME}-client")
set(SERVER_NAME "${PROJECT_NAME}-server")

add_subdirectory(${CMAKE_SOURCE_DIR}/Client/ ${CMAKE_SOURCE_DIR}/bin/client/)
add_subdirectory(${CMAKE_SOURCE_DIR}/Server/ ${CMAKE_SOURCE_DIR}/bin/server/)