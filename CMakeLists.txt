cmake_minimum_required(VERSION 3.10)

# set the project name
project(flightpulsemonitor)

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
