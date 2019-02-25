aux_source_directory(. SRCFILES)
include_directories(.. ${SDL2_INCLUDE_DIR})
add_executable(main ${SRCFILES})
target_link_libraries(main SDL_Engine)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})