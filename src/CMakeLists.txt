file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        )

add_library(game_src STATIC
        ${SRC_FILES}
        )

target_link_libraries(game_src GLEW)
target_include_directories(game_src PUBLIC ${CMAKE_SOURCE_DIR}/includes)