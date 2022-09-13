cmake_minimum_required(VERSION 3.20)
project(opengl)

set(CMAKE_CXX_STANDARD 14)


INCLUDE_DIRECTORIES(/System/Library/Frameworks)
FIND_LIBRARY(COCOA_LIBRARY Cocoa)
FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
FIND_LIBRARY(IOKit_LIBRARY IOKit)
FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})

set(RENDER_LIBRARY_path ./dep/glfw/lib)
set(RENDER_INCLUDE ./dep/glfw/include)
set(RENDER_LIBRARY glfw3)

set(GLAD_src ./dep/glad/src/glad.c)
set(GLAD_header ./dep/glad/include)

include_directories(${RENDER_INCLUDE}
        ${GLAD_header})

link_directories(${RENDER_LIBRARY_path})
set(GAME_src ${GLAD_src} games.cpp)

add_executable(game ${GAME_src})

target_link_libraries(game ${APPLE_LIBS} ${RENDER_LIBRARY})


