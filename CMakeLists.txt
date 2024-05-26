cmake_minimum_required(VERSION 3.25)
project(shark)

set(CMAKE_CXX_STANDARD 17)

# Add executable and link with Raylib
add_executable(shark src/text.cpp src/shader.h)

# Include dir for SharkEditor
target_include_directories(shark PRIVATE include lib/freetype/include lib/glew/include lib/glm/include lib/glfw/include)

# Lib dir
target_link_directories(shark PRIVATE lib/freetype/build lib/glew/lib lib/glm/build/glm lib/glfw/build/src)

target_link_libraries(shark freetype GLEW glm glfw3 GL GLX)