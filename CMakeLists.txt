CMAKE_MINIMUM_REQUIRED(VERSION 3.21)

# Project Info
PROJECT(
        wasm
        VERSION 0.1
        DESCRIPTION "Cube Shuffle")

if(EMSCRIPTEN)
    ADD_DEFINITIONS(-std=c++11 -O3)
    SET(OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/build/wasm)
    MESSAGE("EMSCRIPTEN COMPILE START!!!")
else()
    SET(CMAKE_CXX_STANDARD 17)
    SET(CMAKE_EXE_LINKER_FLAGS "-framework OpenGL")
    SET(OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/build/mac)
    LINK_LIBRARIES(
            libSDL2.dylib
            libGLEW.dylib )
    INCLUDE_DIRECTORIES (
            /usr/local/Cellar/sdl2/2.0.22/include
            /usr/local/Cellar/glew/2.2.0_1/include )
    LINK_DIRECTORIES (
            /usr/local/Cellar/sdl2/2.0.22/lib
            /usr/local/Cellar/glew/2.2.0_1/lib )
    MESSAGE("CPP COMPILE START!!!")
endif()




ADD_SUBDIRECTORY(Framework libs/glm)
ADD_EXECUTABLE( ${PROJECT_NAME} main.cpp )
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC opengl_engine)


if(EMSCRIPTEN)
    SET_TARGET_PROPERTIES(
            ${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "-s USE_SDL=2 -s \"EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']\" -s USE_GLFW=3 -O3 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS=\"['png']\" --preload-file ${CMAKE_CURRENT_LIST_DIR}/data@data/"
            RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    )
else()
    TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC SDL2)
    TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC GLEW)
    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
endif()

