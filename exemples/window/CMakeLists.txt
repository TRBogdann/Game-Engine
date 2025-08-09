cmake_minimum_required(VERSION 3.10)
project(TerrainTest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add program_main.cpp and all other source files
set(SOURCES
    main.cpp
    ../../files/files.cpp
    ../../graphics/buffers/buffers.cpp
    ../../graphics/shaders/shaders.cpp
    ../../graphics/texture/texture.cpp
    ../../graphics/camera/camera.cpp
    ../../graphics/transformations/transformations.cpp
    ../../graphics/mesh/mesh.cpp
    ../../graphics/window/window.cpp
    ../../graphics/program/program.cpp
    ../../graphics/renderer/renderer.cpp
    ../../graphics/surface/surface.cpp
    ../../cpu-math/math.cpp
    ../../graphics/model/model.cpp
)

# Create the executable
add_executable(program ${SOURCES})

# Find OpenGL and pkg-config
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

# Include directories (from pkg-config)
include_directories(
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(program
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    EGL
    OpenGL::GL
)



