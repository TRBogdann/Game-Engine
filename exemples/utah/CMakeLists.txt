cmake_minimum_required(VERSION 3.10)
project(UTAHTEAPOT)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add program_main.cpp and all other source files
set(SOURCES
    main.cpp
      ../../src/exceptions/exceptions.cpp
    ../../src/string-utils/string_utils.cpp
    ../../src/files/files.cpp
    ../../src/graphics/buffers/buffers.cpp
    ../../src/graphics/shaders/shaders.cpp
    ../../src/graphics/texture/texture.cpp
    ../../src/graphics/camera/camera.cpp
    ../../src/graphics/transformations/transformations.cpp
    ../../src/graphics/mesh/mesh.cpp
    ../../src/graphics/window/window.cpp
    ../../src/graphics/program/program.cpp
    ../../src/graphics/renderer/renderer.cpp
    ../../src/graphics/surface/surface.cpp
    ../../src/cpu-math/math.cpp
    ../../src/graphics/model/model.cpp
    ../../src/graphics/blender/blender.cpp
    ./tools/tools.cpp
    ./event_handler/handler.cpp
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
    imgui
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    EGL
    OpenGL::GL
)



