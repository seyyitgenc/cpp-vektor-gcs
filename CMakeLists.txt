cmake_minimum_required(VERSION 3.10)

# set the project name
project(flightpulsemonitor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB SOURCES 
    "imgui/*.*"
    "imgui/backends/imgui_impl_glfw.*"
    "imgui/backends/imgui_impl_opengl3.*"
    "src/*.*"
    "src/GUI/*.*")

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC imgui)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)

# Enable all warnings for GCC/Clang
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/debug/")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/release/")
endif(CMAKE_BUILD_TYPE MATCHES Debug)
