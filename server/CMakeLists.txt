#server cmake file

file(GLOB SERVER_SOURCE "src/*.cpp")

add_executable(${SERVER_NAME} ${SERVER_SOURCE})

target_include_directories(${SERVER_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/common"
)

# Enable all warnings for GCC/Clang
target_compile_options(${SERVER_NAME} PRIVATE -Wall -Wextra -Wpedantic -std=c++23)
