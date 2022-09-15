cmake_minimum_required(VERSION 3.20)
project(opengl)

set(CMAKE_CXX_STANDARD 14)

if(APPLE)
    INCLUDE_DIRECTORIES(/System/Library/Frameworks)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
    FIND_LIBRARY(IOKit_LIBRARY IOKit)
    FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
    MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
    SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
endif()

set(RENDER_LIBRARY_path ./dep/glfw/lib)
set(RENDER_INCLUDE ./dep/glfw/include)
set(RENDER_LIBRARY glfw3)

set(GLAD_src ./dep/glad/src/glad.c)
set(GLAD_header ./dep/glad/include)
set(UTIL_src shader.cpp)

include_directories(${RENDER_INCLUDE}
        ${GLAD_header})

link_directories(${RENDER_LIBRARY_path})

set(GAME_src ${GLAD_src} ${UTIL_src} games.cpp)
set(TEST_src ${GLAD_src} test.cpp)

set(TARGETS_LIST
        GAME
        TEST)

foreach(TARGET ${TARGETS_LIST})
    set(TARGET_src "${TARGET}_src")
    message(${TARGET_src})
    add_executable(${TARGET} ${${TARGET_src}})
    target_link_libraries(${TARGET} ${APPLE_LIBS} ${RENDER_LIBRARY})
    if (APPLE)
        set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
        set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
        set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
    endif(APPLE)
endforeach(TARGET)

macro(makeLink src dest target)
    add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}  DEPENDS  ${dest} COMMENT "mklink ${src} -> ${dest}")
endmacro()

if(APPLE)
    file(GLOB SHADERS
            "res/shader/*.vs"
            "res/shader/*.fs")
    foreach(SHADER ${SHADERS})
        get_filename_component(SHADERNAME ${SHADER} NAME)
        makeLink(${SHADER} ${CMAKE_BINARY_DIR}/bin/${SHADERNAME} GAME)
    endforeach(SHADER)
endif(APPLE)



