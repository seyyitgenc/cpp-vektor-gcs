# client cmake file

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB SOURCES
    "${CMAKE_SOURCE_DIR}/vendor/imgui/*.*"
    "${CMAKE_SOURCE_DIR}/vendor/implot/*.*"
    "src/*.*"
    "src/GUI/*.*"

    "${CMAKE_SOURCE_DIR}/Common/*.cpp"
    "${CMAKE_SOURCE_DIR}/Common/*.hpp"
    "${CMAKE_SOURCE_DIR}/Common/Protocl/*.hpp"
    )
    

add_executable(${CLIENT_NAME} ${SOURCES})

target_include_directories(${CLIENT_NAME} PUBLIC 
    "${CMAKE_SOURCE_DIR}/vendor/imgui"
    "${CMAKE_SOURCE_DIR}/vendor/implot"
    "${CMAKE_SOURCE_DIR}/"
)

target_link_libraries(${CLIENT_NAME} glfw OpenGL::GL)

# Enable all warnings for GCC/Clang
target_compile_options(${CLIENT_NAME} PRIVATE -Wall -Wextra -Wpedantic -std=c++23)
target_link_options(${CLIENT_NAME} PRIVATE -fsanitize=address,undefined)
