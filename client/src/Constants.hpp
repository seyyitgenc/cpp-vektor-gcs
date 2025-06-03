#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

// Window dimensions
constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

// OpenGL profile
constexpr int OPENGL_PROFILE = GLFW_OPENGL_CORE_PROFILE;

// Application name
constexpr const char* APP_NAME = "Flight Pulse Monitor";

// Message types
enum class MessageType : uint8_t {
    Info,
    Warning,
    Error,
    Debug
};

#endif