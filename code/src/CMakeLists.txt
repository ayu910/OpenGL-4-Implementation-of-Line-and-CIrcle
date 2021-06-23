cmake_minimum_required(VERSION 3.16)
project(pa1)
set(CMAKE_CXX_STANDARD 17)

# packages to find

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)

# all sources

set(ALL_INCLUDE_DIRS
        ${GLEW_INCLUDE_DIRS}
        ${OPENCV_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${OPENGL_EGL_INCLUDE_DIRS}
        include
        )

set(ALL_LIBRARIES
        ${OpenCV_LIBS}
        dl
        GLEW::GLEW
        glfw
        OpenGL::GL
        OpenGL::OpenGL
        OpenGL::GLU
        OpenGL::GLX
        OpenGL::EGL
        pthread
        )

# all definitions and options

set(ALL_COMPILE_DEFS

        )

set(ALL_COMPILE_OPTS

        )

# executable target(s)

add_executable(pa1
        src/glad/glad.c
        src/learnopengl/pa1.cpp
        )
target_compile_definitions(pa1 PUBLIC ${ALL_COMPILE_DEFS})
target_compile_options(pa1 PUBLIC ${ALL_COMPILE_OPTS})
target_include_directories(pa1 PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(pa1 ${ALL_LIBRARIES})
