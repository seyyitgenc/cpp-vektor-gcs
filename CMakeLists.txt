cmake_minimum_required(VERSION 3.10)

# set the project name
project(flightpulsemonitor)

set(CLIENT_NAME "${PROJECT_NAME}-client")
set(SERVER_NAME "${PROJECT_NAME}-server")

add_subdirectory(${CMAKE_SOURCE_DIR}/client/ ${CMAKE_SOURCE_DIR}/bin/client/)
add_subdirectory(${CMAKE_SOURCE_DIR}/server/ ${CMAKE_SOURCE_DIR}/bin/server/)