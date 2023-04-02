file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Render/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Node/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Util/*.cpp
        )

add_library(opengl_engine STATIC
        precompiled.h
        ${SRC_FILES}
        )

target_link_libraries(opengl_engine GLEW)
target_include_directories(opengl_engine PUBLIC ${CMAKE_SOURCE_DIR}/includes)