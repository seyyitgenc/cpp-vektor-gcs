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

constexpr int BUFFER_SIZE = 1024; // Size of the buffer for network communication

constexpr int CLIENT_PORT = 8080; // Port for the client
constexpr int SERVER_PORT = 8081; // Port for the server

#endif