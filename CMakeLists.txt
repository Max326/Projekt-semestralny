cmake_minimum_required(VERSION 3.22)
project(MyProject)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

# Set OpenGL preference
set(OpenGL_GL_PREFERENCE GLVND)

file(GLOB SOURCES "src/*.cpp" "*.cpp")

add_executable(MyExecutable ${SOURCES})

# Find Raylib
find_package(raylib REQUIRED)

# Link Raylib to your executable
target_link_libraries(MyExecutable PRIVATE raylib)
